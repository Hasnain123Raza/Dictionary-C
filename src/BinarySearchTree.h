#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "SinglyLinkedList.h"

#define KEY_WORD_LENGTH 16

typedef struct BinarySearchTreeNode {
    char word[KEY_WORD_LENGTH + 1];
    SinglyLinkedListNode *definitions;

    struct BinarySearchTreeNode *left;
    struct BinarySearchTreeNode *right;
} BinarySearchTreeNode;

typedef BinarySearchTreeNode Dictionary;

/* Constructor and Destructor */

Dictionary *createDictionary(char *word, char *definition);
void destroyDictionary(Dictionary *dictionary);

/* Dictionary Operations */

int insertWordDictionary(Dictionary *dictionary, char *word, char *definition);
int removeWordDictionary(Dictionary *dictionary, char *word);
int removeDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex);
Definitions *searchWordDictionary(Dictionary *dictionary, char *word);
Definition *searchDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex);

#endif