#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "frequency_table.h"
#include "text_generator.h"

#include <math.h>

#define MAX_LINE_LENGTH 256

void loadFrequencyTableFromCSV(const char *filename, WordRelation **wordRelations) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *word = strtok(line, ",");
        char *nextWord = strtok(NULL, ",");

        float frequency = atof(strtok(NULL, ","));

        printf("Word: %s, Next word: %s, Frequency: %f\n", word, nextWord, frequency);


        WordRelation *current = *wordRelations;
        while (current != NULL && strcmp(current->word, word) != 0) {
            current = current->next;
        }

        if (current == NULL) {
            current = createWordRelation(word);
            current->next = *wordRelations;
            *wordRelations = current;
        }

        NextWordRelation *next = current->nextWords;
        while (next != NULL && strcmp(next->word, nextWord) != 0) {
            next = next->next;
        }

        if (next == NULL) {
            next = createNextWordRelation(nextWord);
            next->frequency = frequency;
            next->next = current->nextWords;
            current->nextWords = next;
        }
    }

    fclose(file);
}

char *getRandomNextWord(WordRelation *wordRelation) {
    float totalFrequency = 0.0;
    NextWordRelation *currentNext = wordRelation->nextWords;
    while (currentNext != NULL) {
        totalFrequency += currentNext->frequency;
        currentNext = currentNext->next;
    }

    float r = (float)rand() / RAND_MAX * totalFrequency;
    float cumulativeProbability = 0.0;
    currentNext = wordRelation->nextWords;
    while (currentNext != NULL) {
        cumulativeProbability += currentNext->frequency;
        if (r <= cumulativeProbability) {
            return currentNext->word;
        }
        currentNext = currentNext->next;
    }
    return wordRelation->nextWords ? wordRelation->nextWords->word : NULL;
}

WordRelation *getRandomStartingWord(WordRelation *wordRelations) {
    int count = 0;
    WordRelation *current = wordRelations;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    int randomIndex = rand() % count;
    current = wordRelations;
    for (int i = 0; i < randomIndex; i++) {
        current = current->next;
    }

    return current;
}


void generateRandomText(WordRelation *wordRelations, int wordCount) {
    if (wordRelations == NULL) {
        printf("The frequency table is empty.\n");
        return;
    }

    FILE *file = fopen("generated_text.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    } else {
        printf("File opened successfully.\n");
    }

    srand(time(NULL));

    WordRelation *currentWord = wordRelations;
    int totalWords = 0;
    for (WordRelation *wr = wordRelations; wr != NULL; wr = wr->next) {
        totalWords++;
    }

    for (int i = 0; i < wordCount; i++) {
        printf("Iteration: %d\n", i);
        if (currentWord == NULL) {
            int randomIndex = rand() % totalWords;
            currentWord = wordRelations;
            for (int j = 0; j < randomIndex; j++) {
                currentWord = currentWord->next;
            }
        }

        fprintf(file, "%s", currentWord->word);
        fflush(file);
        printf("Writing word to file: %s\n", currentWord->word);

        char *nextWord = getRandomNextWord(currentWord);
        WordRelation *temp = wordRelations;
        while (temp != NULL && strcmp(temp->word, nextWord) != 0) {
            temp = temp->next;
        }

        if (temp != NULL) {
            currentWord = temp;
        } else {
            currentWord = wordRelations;
        }

        if (i < wordCount - 1) {
            fprintf(file, " ");
            printf(" ");
        }
    }

    fprintf(file, "\n");
    printf("\n");

    fclose(file);
}
