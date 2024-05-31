#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include "frequency_table.h"
#include "multi_process_frequency_table.h"
// Function to load the frequency table from a CSV file
// filename: The name of the CSV file to load the frequency table from
// wordRelations: Pointer to the head of the linked list of word relations
void loadFrequencyTableFromCSV(const char *filename, WordRelation **wordRelations);


// Function to generate random text based on the frequency table
// wordRelations: The head of the linked list of word relations
// wordCount: The number of words to generate
void generateRandomText(WordRelation *wordRelations, int wordCount);
#endif // TEXT_GENERATOR_H
