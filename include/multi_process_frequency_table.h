#ifndef MULTI_PROCESS_FREQUENCY_TABLE_H
#define MULTI_PROCESS_FREQUENCY_TABLE_H

#define MAX_WORD_LENGTH 50

typedef struct MultiProcessNextWordRelation {
    char word[MAX_WORD_LENGTH];
    int count;
    float frequency;
    long next;  // offset to the next MultiProcessNextWordRelation
} MultiProcessNextWordRelation;

typedef struct MultiProcessWordRelation {
    char word[MAX_WORD_LENGTH];
    int totalNextWords;
    long nextWords;  // offset to the first MultiProcessNextWordRelation
    long next;  // offset to the next MultiProcessWordRelation
} MultiProcessWordRelation;

#endif // MULTI_PROCESS_FREQUENCY_TABLE_H