#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 30

typedef struct Node {
    char word[MAX_WORD_LENGTH];
    int count;
    struct Node *next;
} Node;

typedef struct WordNode {
    char word[MAX_WORD_LENGTH];
    Node *nextWords;
    struct WordNode *next;
} WordNode;

char *removePunctuation(char *word) {
    if (strlen(word) == 1 && (word[0] == '.' || word[0] == '?' || word[0] == '!')) {
        return word;
    }
    int i, j = 0;
    char *output = malloc(strlen(word) + 1);
    for(i = 0; i < strlen(word); i++) {
        if(isalpha(word[i]) || word[i] == '\'') {
            output[j++] = word[i];
        }
    }
    output[j] = '\0';
    return output;
}

WordNode *createWordNode(char *word) {
    WordNode *newNode = malloc(sizeof(WordNode));
    if (strlen(word) == 1 && (word[0] == '.' || word[0] == '?' || word[0] == '!')) {
        strcpy(newNode->word, word);
    } else {
        strcpy(newNode->word, removePunctuation(word));
    }
    newNode->nextWords = NULL;
    newNode->next = NULL;
    return newNode;
}

Node *createNode(char *word) {
    Node *newNode = malloc(sizeof(Node));
    if (strlen(word) == 1 && (word[0] == '.' || word[0] == '?' || word[0] == '!')) {
        strcpy(newNode->word, word);
    } else {
        strcpy(newNode->word, removePunctuation(word));
    }
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

void addWord(WordNode *wordNode, char *nextWord) {
    Node *current = wordNode->nextWords;
    while (current != NULL) {
        if (strcasecmp(current->word, nextWord) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }
    Node *newNode = createNode(nextWord);
    newNode->next = wordNode->nextWords;
    wordNode->nextWords = newNode;
}

void processText(char *text, WordNode **wordNodes) {
    char word[MAX_WORD_LENGTH] = "";
    int wordLength = 0;
    WordNode *lastNode = createWordNode(".");
    *wordNodes = lastNode;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            word[wordLength++] = tolower(text[i]);
        } else if (text[i] == '\'') {
            word[wordLength++] = text[i];
            if (wordLength > 0) {
                word[wordLength] = '\0';
                WordNode *newNode = createWordNode(word);
                addWord(lastNode, word);
                lastNode->next = newNode;
                lastNode = newNode;
                wordLength = 0;
            }
        } else if (text[i] == ' ' || text[i] == ',' || text[i] == '.' || text[i] == '?' || text[i] == '!') {
            if (wordLength > 0) {
                word[wordLength] = '\0';
                WordNode *newNode = createWordNode(word);
                addWord(lastNode, word);
                lastNode->next = newNode;
                lastNode = newNode;
                wordLength = 0;
            }
            if (text[i] != ' ') {
                word[wordLength++] = text[i];
                word[wordLength] = '\0';
                WordNode *newNode = createWordNode(word);
                addWord(lastNode, word);
                lastNode->next = newNode;
                lastNode = newNode;
                wordLength = 0;
            }
        }
    }
    if (wordLength > 0) {
        word[wordLength] = '\0';
        WordNode *newNode = createWordNode(word);
        addWord(lastNode, word);
        lastNode->next = newNode;
    }
}

void writeCSV(WordNode *wordNodes, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    WordNode *currentWordNode = wordNodes;
    while (currentWordNode != NULL) {
        Node *currentNode = currentWordNode->nextWords;
        while (currentNode != NULL) {
            fprintf(file, "%s,%s,%d\n", currentWordNode->word, currentNode->word, currentNode->count);
            printf("Writing to file: %s,%s,%d\n", currentWordNode->word, currentNode->word, currentNode->count);
            currentNode = currentNode->next;
        }
        currentWordNode = currentWordNode->next;
    }
    if (fclose(file) != 0) {
        perror("Error closing file");
    }
}

int main() {
    char text[] = "Cosa dicono le previsioni del tempo? Oggi c'era molto caldo!";
    WordNode *wordNodes = NULL;
    processText(text, &wordNodes);
    writeCSV(wordNodes, "output.csv");
    return 0;
}