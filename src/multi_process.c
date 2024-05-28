// multi_process.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "multi_process_frequency_table.h"
#include "text_generator.h"

#define SHM_SIZE 1024 * 1024 // 1MB shared memory

void create_frequency_table() {
    WordRelation *wordRelations = NULL;
    char text[1024];
    printf("Enter text to build frequency table:\n");
    scanf(" %[^\n]", text);
    processText(text, &wordRelations);
    writeCSV(wordRelations, "output.csv");
    freeFrequencyTable(wordRelations);
}

void load_and_serialize_frequency_table(char *shm_ptr) {
    WordRelation *wordRelations = NULL;
    loadFrequencyTableFromCSV("output.csv", &wordRelations);
    int fd = shm_open("/frequency_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHM_SIZE);
    size_t dataSize = serializeWordRelations(wordRelations, shm_ptr);
    // Do not unmap or close the shared memory here
    // Remove the call to freeFrequencyTable here
}

void printWordRelations(WordRelation *wordRelations) {
    WordRelation *current = wordRelations;
    while (current != NULL) {
        printf("Word: %s\n", current->word);
        NextWordRelation *next = current->nextWords;
        while (next != NULL) {
            printf("Next word: %s, Frequency: %f\n", next->word, next->frequency);
            next = next->next;
        }
        current = current->next;
    }
}

void generate_text_from_frequency_table(int wordCount, char *shm_ptr_arg) {
    int fd = shm_open("/frequency_shm", O_RDONLY, 0666);
    if (fd == -1) {
        perror("shm_open failed in generate_text_from_frequency_table");
        exit(EXIT_FAILURE);
    }

    char *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap failed in generate_text_from_frequency_table");
        close(fd);
        exit(EXIT_FAILURE);
    }

    WordRelation *wordRelations = deserializeWordRelations(shm_ptr);
    if (wordRelations == NULL) {
        fprintf(stderr, "deserializeWordRelations failed in generate_text_from_frequency_table\n");
        munmap(shm_ptr, SHM_SIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    printWordRelations(wordRelations);  // Print the deserialized WordRelation linked list

    generateRandomText(wordRelations, wordCount);
    munmap(shm_ptr, SHM_SIZE);
    close(fd);
}

void multiProcessVersion() {
    int wordCount;

    printf("Enter number of words to generate:\n");
    scanf("%d", &wordCount);

    pid_t pid1, pid2, pid3;
    int status;

    // Create shared memory for the frequency table
    int fd = shm_open("/frequency_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHM_SIZE);
    char *shm_ptr = mmap(NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    // Process 1: Create frequency table
    if ((pid1 = fork()) == 0) {
        create_frequency_table();
        exit(EXIT_SUCCESS);
    }

    waitpid(pid1, &status, 0);

    // Process 2: Load and serialize frequency table to shared memory
    if ((pid2 = fork()) == 0) {
        load_and_serialize_frequency_table(shm_ptr);  // Pass the shared memory pointer
        exit(EXIT_SUCCESS);
    }

    waitpid(pid2, &status, 0);

    // Process 3: Generate text from the serialized frequency table
    if ((pid3 = fork()) == 0) {
        generate_text_from_frequency_table(wordCount, shm_ptr);  // Pass the shared memory pointer
        exit(EXIT_SUCCESS);
    }

    waitpid(pid3, &status, 0);

    // Clean up shared memory
    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    shm_unlink("/frequency_shm");

    printf("All processes completed.\n");
}
