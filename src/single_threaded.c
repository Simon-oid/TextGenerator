#include <stdio.h>
#include <stdlib.h>
#include "frequency_table.h"
#include "text_generator.h"

// Function to run the single-threaded version of the program
void singleThreadedVersion() {

    // Initialize the head of the linked list of word relations to NULL
    WordRelation *wordRelations = NULL;

    // Build the frequency table from the input text file
    printf("Building frequency table from input.txt...\n");
    processTextFromFile("input.txt", &wordRelations);
    writeCSV(wordRelations, "output.csv");
    printf("Frequency table written to output.csv successfully.\n");

    // Load the frequency table from the CSV file and generate random text
    loadFrequencyTableFromCSV("output.csv", &wordRelations);

    // Check if the frequency table is loaded successfully
    if (wordRelations == NULL) {
        printf("Error: Frequency table not loaded.\n");
        freeFrequencyTable(wordRelations);
        return;
    }

    // Ask the user for the number of words to generate
    printf("Enter number of words to generate:\n");
    int wordCount;
    scanf("%d", &wordCount);
    generateRandomText(wordRelations, wordCount);

    // Free the memory used by the word relations
    freeFrequencyTable(wordRelations);
}
