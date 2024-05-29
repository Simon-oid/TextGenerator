// main.c
#include <stdio.h>
#include <stdlib.h>
#include "frequency_table.h"
#include "text_generator.h"
#include "single_threaded.h"
#include "multi_process.h"

void processTextAndGenerateFrequencyTableFromFile(WordRelation **wordRelations) {
    // char filename[256];
    // printf("Enter filename of the text file to build frequency table:\n");
    // scanf("%s", filename);

    processTextFromFile("input.txt", wordRelations);
    writeCSV(*wordRelations, "output.csv");
    printf("Frequency table written to output.csv successfully.\n");
}

void loadFrequencyTableAndGenerateText(WordRelation **wordRelations) {
    loadFrequencyTableFromCSV("output.csv", wordRelations);

    if (*wordRelations == NULL) {
        printf("Error: Frequency table not loaded.\n");
        return;
    }

    printf("Enter number of words to generate:\n");
    int wordCount;
    scanf("%d", &wordCount);
    generateRandomText(*wordRelations, wordCount);
}

int main() {
    int option;
    WordRelation *wordRelations = NULL;

    do {
        printf("\nOptions:\n");
        printf("  1 - Build frequency table\n");
        printf("  2 - Generate random text\n");
        printf("  3 - Single-threaded version\n");
        printf("  4 - Multi-process version\n");
        printf("  0 - Exit\n");
        printf("Choose an option: ");
        scanf(" %d", &option);  // Add a space before %d

        switch (option) {
            case 0:
                printf("Exiting...\n");
            break;
            case 1:
                processTextAndGenerateFrequencyTableFromFile(&wordRelations);
            break;
            case 2:
                loadFrequencyTableAndGenerateText(&wordRelations);
            break;
            case 3:
                singleThreadedVersion();
            break;
            case 4:
                multiProcessVersion();
            break;
            default:
                printf("Invalid option. Please choose again.\n");
        }
    } while (option != 0);

    freeFrequencyTable(wordRelations);
    return 0;
}
