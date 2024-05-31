#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "frequency_table.h"
#include "text_generator.h"
#include <ctype.h>
#include <math.h>

#define MAX_LINE_LENGTH 256

// Function to load the frequency table from a CSV file
// filename: The name of the CSV file to load the frequency table from
// wordRelations: Pointer to the head of the linked list of word relations
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

        // printf("Word: %s, Next word: %s, Frequency: %f\n", word, nextWord, frequency);

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
        } else {
            // Update the frequency of the existing NextWordRelation
            next->frequency = frequency;
        }
    }

    fclose(file);
}

// Function to get a random starting word from a list of word relations
// wordRelations: The head of the linked list of word relations
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

// Function to get a random next word from a word relation
// wordRelation: The word relation to get the next word from
char *getRandomNextWord(WordRelation *wordRelation) {

    // Calculate the total frequency
    float totalFrequency = 0.0f;
    NextWordRelation *currentNext = wordRelation->nextWords;
    while (currentNext != NULL) {
        totalFrequency += currentNext->frequency;
        currentNext = currentNext->next;
    }

    // Generate a random number between 0 and the total frequency
    float randomFrequency = ((float)rand()/(float)(RAND_MAX)) * totalFrequency;

    // Find the word where the cumulative frequency is just greater than or equal to the random number
    float cumulativeFrequency = 0.0f;
    currentNext = wordRelation->nextWords;
    char *nextWord = NULL;
    while (currentNext != NULL) {
        cumulativeFrequency += currentNext->frequency;
        if (cumulativeFrequency >= randomFrequency) {
            nextWord = currentNext->word;
            break;
        }
        currentNext = currentNext->next;
    }

    // If no next word with non-zero frequency is found, return the first word in the list
    return nextWord != NULL ? nextWord : wordRelation->nextWords->word;
}

// Function to generate random text based on the frequency table
// wordRelations: The head of the linked list of word relations
// wordCount: The number of words to generate
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

    WordRelation *currentWord = getRandomStartingWord(wordRelations);
    for (int i = 0; i < wordCount; i++) {
        char *nextWord = getRandomNextWord(currentWord);  // Pass currentWord

        fprintf(file, "%s", nextWord);  // Write nextWord to the file

        // Update currentWord to the word that was just written
        WordRelation *temp = wordRelations;
        while (temp != NULL && strcmp(temp->word, nextWord) != 0) {
            temp = temp->next;
        }
        if (temp != NULL) {
            currentWord = temp;
        } else {
            currentWord = getRandomStartingWord(wordRelations);
        }

        if (i < wordCount - 1) {
            fprintf(file, " ");
        }
    }

    fprintf(file, "\n");
    printf("\n");

    fclose(file);
}
