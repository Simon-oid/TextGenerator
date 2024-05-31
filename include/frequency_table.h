#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

// Maximum word length
#define MAX_WORD_LENGTH 50

// Structure to hold the next word and its frequency
typedef struct NextWordRelation {
    char word[MAX_WORD_LENGTH];
    int count;
    float frequency;
    float cumulativeFrequency;  // New field
    struct NextWordRelation *next;
} NextWordRelation;

// Structure to hold a word ans its relations to other words
typedef struct WordRelation {
    char word[MAX_WORD_LENGTH];
    int totalNextWords;
    NextWordRelation *nextWords;
    struct WordRelation *next;
} WordRelation;

// Function to remove punctuation from a word
char *removePunctuation(const char *word);
// Function to create a new next word relation
NextWordRelation *createNextWordRelation(const char *word);
// Function to create a new word relation
WordRelation *createWordRelation(const char *word);
// Function to add a next word relation to a word relation
void addNextWordRelation(WordRelation *wordRelation, const char *nextWord);
// Function to process a text and build word relations
void processText(const char *text, WordRelation **wordRelations);
// Function to write the word relations to a CSV file
void writeCSV(WordRelation *wordRelations, const char *filename);
// Function to free the memory used by the word relations
void freeFrequencyTable(WordRelation *wordRelations);
// Function to process a text file and build word relations
void processTextFromFile(const char *filename, WordRelation **wordRelations);
// Function to serialize word relations into shared memory
size_t serializeWordRelations(WordRelation *wordRelations, char *shm_ptr);
// Function to deserialize word relations from shared memory
WordRelation* deserializeWordRelations(char *shm_ptr);

#endif // FREQUENCY_TABLE_H
