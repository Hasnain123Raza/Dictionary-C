#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "SinglyLinkedList.h"
#include "WordsArray.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define PREFIX_BUFFER_SIZE 256

typedef struct BinarySearchTreeNode {
    char word[KEY_WORD_LENGTH + 1];
    Definitions *definitions;

    struct BinarySearchTreeNode *left;
    struct BinarySearchTreeNode *right;
} BinarySearchTreeNode;

typedef BinarySearchTreeNode Dictionary;

/* Constructor and Destructor */

Dictionary *createDictionary(char *word, Definitions *definitions);
void destroyDictionary(Dictionary *dictionary);

Dictionary *buildDictionaryFromWordsArray(WordsArray *wordsArray);

/* Dictionary Operations */

int insertWordDictionary(Dictionary *dictionary, char *word, Definitions *definitions);
int insertDefinitionDictionary(Dictionary *dictionary, char *word, Definition *definition);
Dictionary *removeWordDictionary(Dictionary *dictionary, char *word);
Dictionary *removeDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex);
Definitions *searchWordDictionary(Dictionary *dictionary, char *word);
Definition *searchDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex);
unsigned int getMatchesDictionary(Dictionary *dictionary, char *prefix, char *words[], unsigned int maxWords);

void printDictionary(Dictionary *dictionary, char *prefix, int isLeft);

#endif