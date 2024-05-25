#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "frequency_table.h"
#include "text_generator.h"

#define SHM_SIZE 1024

void process1(int shm_id) {
    printf("Enter text to build frequency table:\n");
    char text[1024];
    scanf(" %[^\n]", text);

    WordRelation *wordRelations = shmat(shm_id, NULL, 0);
    processText(text, &wordRelations);
    printf("Process 1: Frequency table built.\n");
    shmdt(wordRelations);
    exit(0); // End the process after task completion
}

void process2(int shm_id) {
    WordRelation *wordRelations = shmat(shm_id, NULL, 0);
    if (wordRelations == (WordRelation *)-1) {
        perror("shmat");
        exit(1);
    }

    if (wordRelations == NULL) {
        printf("Process 2: Error: No word relations to write.\n");
        exit(1);
    }

    // Print the frequency table for debugging
    WordRelation *current = wordRelations;
    while (current != NULL) {
        printf("%s -> ", current->word);
        NextWordRelation *next = current->nextWords;
        while (next != NULL) {
            printf("%s (%f), ", next->word, next->frequency);
            next = next->next;
        }
        printf("\n");
        current = current->next;
    }

    writeCSV(wordRelations, "output.csv");
    printf("Process 2: Frequency table written to output.csv successfully.\n");

    // Verify that the file has contents
    FILE *file = fopen("output.csv", "r");
    if (file == NULL) {
        perror("Process 2: Error opening output.csv");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);

    if (fileSize == 0) {
        printf("Process 2: Error: output.csv is empty.\n");
        exit(1);
    } else {
        printf("Process 2: output.csv is not empty, size: %ld bytes.\n", fileSize);
    }
    shmdt(wordRelations);
    exit(0); // End the process after task completion
}

void process3() {
    // Load frequency table from CSV
    WordRelation *wordRelations = NULL;
    loadFrequencyTableFromCSV("output.csv", &wordRelations);

    if (wordRelations == NULL) {
        printf("Process 3: Error: Frequency table not loaded.\n");
        exit(1);
    }

    printf("Enter number of words to generate:\n");
    int wordCount;
    scanf("%d", &wordCount);
    generateRandomText(wordRelations, wordCount);
    freeFrequencyTable(wordRelations);
    exit(0); // End the process after task completion
}

void multiProcessVersion() {
    int shm_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    pid_t p1, p2, p3;
    int status;

    p1 = fork();
    if (p1 < 0) {
        perror("Error creating process 1");
        exit(1);
    } else if (p1 == 0) {
        process1(shm_id);
    } else {
        waitpid(p1, &status, 0); // Wait for process 1 to complete

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            p2 = fork();
            if (p2 < 0) {
                perror("Error creating process 2");
                exit(1);
            } else if (p2 == 0) {
                process2(shm_id);
            } else {
                waitpid(p2, &status, 0); // Wait for process 2 to complete

                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    p3 = fork();
                    if (p3 < 0) {
                        perror("Error creating process 3");
                        exit(1);
                    } else if (p3 == 0) {
                        process3();
                    } else {
                        waitpid(p3, &status, 0); // Wait for process 3 to complete
                    }
                }
            }
        }
    }

    // Detach and remove shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) < 0) {
        perror("shmctl");
        exit(1);
    }
}
