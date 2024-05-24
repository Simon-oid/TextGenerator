#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#define MAX_WORD_LENGTH 50

typedef struct NextWordRelation {
    char word[MAX_WORD_LENGTH];
    int count;
    float frequency;
    struct NextWordRelation *next;
} NextWordRelation;

typedef struct WordRelation {
    char word[MAX_WORD_LENGTH];
    int totalNextWords;
    NextWordRelation *nextWords;
    struct WordRelation *next;
} WordRelation;

char *removePunctuation(const char *word);
NextWordRelation *createNextWordRelation(const char *word);
WordRelation *createWordRelation(const char *word);
void addNextWordRelation(WordRelation *wordRelation, const char *nextWord);
void processText(const char *text, WordRelation **wordRelations);
void writeCSV(WordRelation *wordRelations, const char *filename);
void freeFrequencyTable(WordRelation *wordRelations);

#endif // FREQUENCY_TABLE_H
