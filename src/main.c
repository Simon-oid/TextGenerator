#include <stdio.h>
#include <stdlib.h>
#include "frequency_table.h"
#include "text_generator.h"

// Uncomment the following lines to enable testing for each component
#define TEST_FREQUENCY_TABLE
//#define TEST_TEXT_GENERATOR

#ifdef TEST_FREQUENCY_TABLE
void testProcessText() {
    char text[] = "Cosa dicono le previsioni del tempo? Previsioni del tempo di oggi: tempo incerto! Previsioni di domani?";
    WordRelation *wordRelations = NULL;
    processText(text, &wordRelations);

    // Print the results for verification
    WordRelation *currentWord = wordRelations;
    while (currentWord != NULL) {
        NextWordRelation *currentNext = currentWord->nextWords;
        while (currentNext != NULL) {
            printf("%s -> %s: %d\n", currentWord->word, currentNext->word, currentNext->count);
            currentNext = currentNext->next;
        }
        currentWord = currentWord->next;
    }

    // Free the memory
    freeFrequencyTable(wordRelations);
}

void testWriteCSV() {
    char text[] = "Cosa dicono le previsioni del tempo? Previsioni del tempo di oggi: tempo incerto! Previsioni di domani?";
    WordRelation *wordRelations = NULL;
    processText(text, &wordRelations);
    writeCSV(wordRelations, "output.csv");
    freeFrequencyTable(wordRelations);
}

int main() {
    testProcessText();
    testWriteCSV();
    return 0;
}
#endif

#ifdef TEST_TEXT_GENERATOR
void testGenerateRandomText() {
    WordRelation *wordRelations = NULL;
    loadFrequencyTableFromCSV("output.csv", &wordRelations);

    // Generate random text
    generateRandomText(wordRelations, 11);

    // Free the memory
    freeFrequencyTable(wordRelations);
}

int main() {
    testGenerateRandomText();
    return 0;
}
#endif

#ifndef TEST_FREQUENCY_TABLE
#ifndef TEST_TEXT_GENERATOR
int main() {
    // Your main program logic
    int option;
    WordRelation *wordRelations = NULL;

    do {
        printf("\nOptions:\n");
        printf("  1 - Build frequency table\n");
        printf("  2 - Generate random text\n");
        printf("  0 - Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                printf("Exiting...\n");
                break;
            case 1: {
                printf("Enter text to build frequency table:\n");
                char text[1024];
                scanf(" %[^\n]", text);

                processText(text, &wordRelations);
                writeCSV(wordRelations, "output.csv");
                printf("Frequency table written to output.csv successfully.\n");
                break;
            }
            case 2: {
                if (wordRelations == NULL) {
                    printf("Error: Frequency table not built.\n");
                    break;
                }
                printf("Enter number of words to generate:\n");
                int wordCount;
                scanf("%d", &wordCount);
                generateRandomText(wordRelations, wordCount);
                break;
            }
            default:
                printf("Invalid option. Please choose again.\n");
        }
    } while (option != 0);

    freeFrequencyTable(wordRelations);
    return 0;
}
#endif
#endif
