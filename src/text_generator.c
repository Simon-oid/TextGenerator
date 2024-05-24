#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "frequency_table.h"
#include "text_generator.h"

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
    float r = (float)rand() / RAND_MAX;
    float cumulativeProbability = 0.0;
    NextWordRelation *currentNext = wordRelation->nextWords;
    while (currentNext != NULL) {
        cumulativeProbability += currentNext->frequency;
        if (r <= cumulativeProbability) {
            return currentNext->word;
        }
        currentNext = currentNext->next;
    }
    return wordRelation->nextWords ? wordRelation->nextWords->word : NULL;
}

void generateRandomText(WordRelation *wordRelations, int wordCount) {
    if (wordRelations == NULL) {
        printf("The frequency table is empty.\n");
        return;
    }

    srand(time(NULL));

    WordRelation *currentWord = wordRelations;
    int totalWords = 0;
    for (WordRelation *wr = wordRelations; wr != NULL; wr = wr->next) {
        totalWords++;
    }

    for (int i = 0; i < wordCount; i++) {
        if (currentWord == NULL) {
            int randomIndex = rand() % totalWords;
            currentWord = wordRelations;
            for (int j = 0; j < randomIndex; j++) {
                currentWord = currentWord->next;
            }
        }

        printf("%s", currentWord->word);

        char *nextWord = getRandomNextWord(currentWord);
        currentWord = wordRelations;
        while (currentWord != NULL && strcmp(currentWord->word, nextWord) != 0) {
            currentWord = currentWord->next;
        }

        if (i < wordCount - 1) {
            printf(" ");
        }
    }
    printf("\n");
}
