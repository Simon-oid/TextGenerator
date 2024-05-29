#include <stdio.h>
#include <stdlib.h>
#include "frequency_table.h"
#include "text_generator.h"

void singleThreadedVersion() {
    WordRelation *wordRelations = NULL;

    // Build frequency table
    printf("Building frequency table from input.txt...\n");
    processTextFromFile("input.txt", &wordRelations);
    writeCSV(wordRelations, "output.csv");
    printf("Frequency table written to output.csv successfully.\n");

    // Load frequency table and generate random text
    loadFrequencyTableFromCSV("output.csv", &wordRelations);

    // Check if the frequency table is loaded successfully
    if (wordRelations == NULL) {
        printf("Error: Frequency table not loaded.\n");
        freeFrequencyTable(wordRelations);
        return;
    }

    printf("Enter number of words to generate:\n");
    int wordCount;
    scanf("%d", &wordCount);
    generateRandomText(wordRelations, wordCount);

    freeFrequencyTable(wordRelations);
}
