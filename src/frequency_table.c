#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "frequency_table.h"
#include "shared.h"

// Function to remove punctuation from a word
// word: The word from which punctuation is to be removed
char *removePunctuation(const char *word) {
    int i, j = 0;
    char *output = malloc(strlen(word) + 1);
    if (output == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < strlen(word); i++) {
        if (isalpha(word[i]) || word[i] == '\'') {
            output[j++] = word[i];
        }
    }
    output[j] = '\0';
    return output;
}

// Function to create a new next word relation
// word: The word for which the next word relation is to be created
NextWordRelation *createNextWordRelation(const char *word) {
    NextWordRelation *newNode = malloc(sizeof(NextWordRelation));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new word relation
// word: The word for which the word relation is to be created
WordRelation *createWordRelation(const char *word) {
    WordRelation *newNode = malloc(sizeof(WordRelation));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->totalNextWords = 0;
    newNode->nextWords = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to add a next word relation to a word relation
// wordRelation: The word relation to which the next word relation is to be added
// nextWord: The next word to be added to the word relation
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

// Function to process a text and build word relations
// text: The text to be processed
// wordRelations: The word relations to be built from the text
void processText(const char *text, WordRelation **wordRelations) {
    char word[MAX_WORD_LENGTH] = "";
    int wordLength = 0;
    WordRelation *lastRelation = NULL;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i]) || text[i] == '\'') {
            word[wordLength++] = tolower(text[i]);  // Convert to lowercase
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

// Function to process a text file and build word relations
// filename: The name of the file to be processed
// wordRelations: The word relations to be built from the text file
void processTextFromFile(const char *filename, WordRelation **wordRelations) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *text = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&text, &len, file)) != -1) {
        processText(text, wordRelations);
    }

    free(text);
    fclose(file);
}

// Function to write the word relations to a CSV file
// wordRelations: The word relations to be written to the CSV file
// filename: The name of the CSV file
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

    fflush(file);
    fclose(file);
}

// Function to free the memory used by the word relations
// wordRelations: The word relations for which the memory is to be freed
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

// Function to serialize word relations into shared memory
// wordRelations: The word relations to be serialized
// shm_ptr: The pointer to the shared memory
size_t serializeWordRelations(WordRelation *wordRelations, char *shm_ptr) {
    size_t offset = 0;
    WordRelation *current = wordRelations;
    while (current != NULL) {
        WordRelation *shm_wordRelation = (WordRelation *)(shm_ptr + offset);
        // Copy the data of the WordRelation structure
        memcpy(shm_wordRelation, current, sizeof(WordRelation));
        offset += sizeof(WordRelation);

        // Serialize the nextWords list
        NextWordRelation *nextWord = current->nextWords;
        while (nextWord != NULL) {
            NextWordRelation *shm_nextWord = (NextWordRelation *)(shm_ptr + offset);
            // Copy the data of the NextWordRelation structure
            memcpy(shm_nextWord, nextWord, sizeof(NextWordRelation));
            offset += sizeof(NextWordRelation);
            nextWord = nextWord->next;
        }

        current = current->next;
    }
    return offset;
}


// Function to deserialize word relations from shared memory
// shm_ptr: The pointer to the shared memory
WordRelation *deserializeWordRelations(char *shm_ptr) {
    size_t offset = 0;
    WordRelation *wordRelations = NULL;
    WordRelation *last = NULL;
    while (offset < SHM_SIZE) {
        WordRelation *shm_wordRelation = (WordRelation *)(shm_ptr + offset);
        if (shm_wordRelation->word[0] == '\0') {  // Check if the word is an empty string
            break;  // End of WordRelation linked list
        }
        WordRelation *new_wordRelation = createWordRelation(shm_wordRelation->word);
        memcpy(new_wordRelation, shm_wordRelation, sizeof(WordRelation));
        offset += sizeof(WordRelation);

        NextWordRelation *lastNextWord = NULL;
        while (offset < SHM_SIZE) {
            NextWordRelation *shm_nextWord = (NextWordRelation *)(shm_ptr + offset);
            if (shm_nextWord->word[0] == '\0' || shm_nextWord->frequency < 0) {  // Check if the word is an empty string or frequency is negative
                break;  // End of NextWordRelation linked list
            }
            NextWordRelation *new_nextWord = createNextWordRelation(shm_nextWord->word);
            memcpy(new_nextWord, shm_nextWord, sizeof(NextWordRelation));
            offset += sizeof(NextWordRelation);

            if (lastNextWord == NULL) {
                new_wordRelation->nextWords = new_nextWord;
            } else {
                lastNextWord->next = new_nextWord;
            }
            lastNextWord = new_nextWord;
        }

        if (last == NULL) {
            wordRelations = new_wordRelation;
        } else {
            last->next = new_wordRelation;
        }
        last = new_wordRelation;
    }
    return wordRelations;
}
