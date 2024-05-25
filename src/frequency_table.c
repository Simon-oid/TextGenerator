#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "frequency_table.h"

char *removePunctuation(const char *word) {
    int i, j = 0;
    char *output = malloc(strlen(word) + 1);
    for (i = 0; i < strlen(word); i++) {
        if (isalpha(word[i]) || word[i] == '\'') {
            output[j++] = word[i];
        }
    }
    output[j] = '\0';
    return output;
}

NextWordRelation *createNextWordRelation(const char *word) {
    NextWordRelation *newNode = malloc(sizeof(NextWordRelation));
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

WordRelation *createWordRelation(const char *word) {
    WordRelation *newNode = malloc(sizeof(WordRelation));
    strcpy(newNode->word, word);
    newNode->totalNextWords = 0;
    newNode->nextWords = NULL;
    newNode->next = NULL;
    return newNode;
}

void addNextWordRelation(WordRelation *wordRelation, const char *nextWord) {
    NextWordRelation *current = wordRelation->nextWords;
    while (current != NULL) {
        if (strcasecmp(current->word, nextWord) == 0) {
            current->count++;
            wordRelation->totalNextWords++;
            return;
        }
        current = current->next;
    }
    NextWordRelation *newNode = createNextWordRelation(nextWord);
    newNode->next = wordRelation->nextWords;
    wordRelation->nextWords = newNode;
    wordRelation->totalNextWords++;
}

void processText(const char *text, WordRelation **wordRelations) {
    char word[MAX_WORD_LENGTH] = "";
    int wordLength = 0;
    WordRelation *lastRelation = NULL;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i]) || text[i] == '\'') {
            word[wordLength++] = text[i]; // Keep the original case
        } else if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == ';' || text[i] == '-') {
            if (wordLength > 0) {
                word[wordLength] = '\0';
                char *cleanWord = removePunctuation(word);

                if (lastRelation != NULL) {
                    addNextWordRelation(lastRelation, cleanWord);
                }

                WordRelation *current = *wordRelations;
                while (current != NULL) {
                    if (strcasecmp(current->word, cleanWord) == 0) {
                        lastRelation = current;
                        break;
                    }
                    current = current->next;
                }

                if (current == NULL) {
                    WordRelation *newRelation = createWordRelation(cleanWord);
                    newRelation->next = *wordRelations;
                    *wordRelations = newRelation;
                    lastRelation = newRelation;
                }

                free(cleanWord);
                wordLength = 0;
            }
            if (text[i] != ' ') {
                char punctuation[2] = { text[i], '\0' };
                if (lastRelation != NULL) {
                    addNextWordRelation(lastRelation, punctuation);
                }

                WordRelation *current = *wordRelations;
                while (current != NULL) {
                    if (strcasecmp(current->word, punctuation) == 0) {
                        lastRelation = current;
                        break;
                    }
                    current = current->next;
                }

                if (current == NULL) {
                    WordRelation *newRelation = createWordRelation(punctuation);
                    newRelation->next = *wordRelations;
                    *wordRelations = newRelation;
                    lastRelation = newRelation;
                }
            }
        } else if (text[i] == ':') {
            // Skip the colon, do nothing
        }
    }

    if (wordLength > 0) {
        word[wordLength] = '\0';
        char *cleanWord = removePunctuation(word);
        if (lastRelation != NULL) {
            addNextWordRelation(lastRelation, cleanWord);
        }

        WordRelation *current = *wordRelations;
        while (current != NULL) {
            if (strcasecmp(current->word, cleanWord) == 0) {
                lastRelation = current;
                break;
            }
            current = current->next;
        }

        if (current == NULL) {
            WordRelation *newRelation = createWordRelation(cleanWord);
            newRelation->next = *wordRelations;
            *wordRelations = newRelation;
        }

        free(cleanWord);
    }
}

void writeCSV(WordRelation *wordRelations, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    WordRelation *currentWord = wordRelations;
    while (currentWord != NULL) {
        NextWordRelation *currentNext = currentWord->nextWords;
        while (currentNext != NULL) {
            fprintf(file, "%s,%s,%f\n", currentWord->word, currentNext->word, (float)currentNext->count / currentWord->totalNextWords);
            currentNext = currentNext->next;
        }
        currentWord = currentWord->next;
    }

    fflush(file); // Ensure all data is written to the file
    fclose(file); // Properly close the file
}


void freeFrequencyTable(WordRelation *wordRelations) {
    WordRelation *currentWord = wordRelations;
    while (currentWord != NULL) {
        WordRelation *tempWord = currentWord;
        NextWordRelation *currentNext = currentWord->nextWords;
        while (currentNext != NULL) {
            NextWordRelation *tempNext = currentNext;
            currentNext = currentNext->next;
            free(tempNext);
        }
        currentWord = currentWord->next;
        free(tempWord);
    }
}
