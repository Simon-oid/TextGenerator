#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>
#include "multi_process_frequency_table.h"
#include "text_generator.h"

#define SHM_SIZE 1024 * 1024 * 10 // 10MB shared memory
#define SEM_NAME "/freq_sem"

// Function to create a frequency table from the input text file
void create_frequency_table() {
    WordRelation *wordRelations = NULL;
    printf("Building frequency table from input.txt...\n");
    processTextFromFile("input.txt", &wordRelations);
    writeCSV(wordRelations, "output.csv");
    freeFrequencyTable(wordRelations);
}

// Function to load the frequency table from a CSV file and serialize it into shared memory
void load_and_serialize_frequency_table(char *shm_ptr, sem_t *sem) {
    WordRelation *wordRelations = NULL;
    loadFrequencyTableFromCSV("output.csv", &wordRelations);

    // Lock semaphore
    sem_wait(sem);

    size_t dataSize = serializeWordRelations(wordRelations, shm_ptr);

    // Unlock semaphore
    sem_post(sem);
}

// Function to generate text from the frequency table stored in shared memory
void generate_text_from_frequency_table(int wordCount, char *shm_ptr, sem_t *sem) {
    // Lock semaphore
    sem_wait(sem);

    WordRelation *wordRelations = deserializeWordRelations(shm_ptr);

    // Unlock semaphore
    sem_post(sem);

    if (wordRelations == NULL) {
        fprintf(stderr, "deserializeWordRelations failed in generate_text_from_frequency_table\n");
        exit(EXIT_FAILURE);
    }

    generateRandomText(wordRelations, wordCount);

}

// Function to run the multi-process version of the program
void multiProcessVersion() {
    int wordCount;

    printf("Enter number of words to generate:\n");
    scanf("%d", &wordCount);

    pid_t pid1, pid2, pid3;
    int status;

    // Create pipes for inter-process communication
    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // Create shared memory for the frequency table
    int fd = shm_open("/frequency_shm", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }
    ftruncate(fd, SHM_SIZE);
    char *shm_ptr = mmap(NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Create semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open failed");
        munmap(shm_ptr, SHM_SIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Process 1: Create frequency table
    if ((pid1 = fork()) == 0) {
        printf("Process 1 (PID: %d) started\n", getpid());
        create_frequency_table();
        printf("Process 1 (PID: %d) completed\n", getpid());


        // Send signal to next process
        close(pipe1[0]);
        write(pipe1[1], "1", 1);
        close(pipe1[1]);

        exit(EXIT_SUCCESS);
    }

    // Wait for signal from previous process
    close(pipe1[1]);
    char buf;
    read(pipe1[0], &buf, 1);
    close(pipe1[0]);

    // Process 2: Load and serialize frequency table to shared memory
    if ((pid2 = fork()) == 0) {
        printf("Process 2 (PID: %d) started\n", getpid());
        load_and_serialize_frequency_table(shm_ptr, sem);
        printf("Shared memory contents after Process 2: %s\n", shm_ptr);
        printf("Process 2 (PID: %d) completed\n", getpid());

        // Send signal to next process
        close(pipe2[0]);
        write(pipe2[1], "1", 1);
        close(pipe2[1]);

        exit(EXIT_SUCCESS);
    }

    // Wait for signal from previous process
    close(pipe2[1]);
    read(pipe2[0], &buf, 1);
    close(pipe2[0]);

    // Process 3: Generate text from the serialized frequency table
    if ((pid3 = fork()) == 0) {
        printf("Process 3 (PID: %d) started\n", getpid());
        printf("Shared memory contents before Process 3: %s\n", shm_ptr);
        generate_text_from_frequency_table(wordCount, shm_ptr, sem);
        printf("Process 3 (PID: %d) completed\n", getpid());
        exit(EXIT_SUCCESS);
    }
    waitpid(pid3, &status, 0);

    // Clean up shared memory and semaphore
    sem_close(sem);
    sem_unlink(SEM_NAME);
    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    shm_unlink("/frequency_shm");

    printf("All processes completed.\n");
}