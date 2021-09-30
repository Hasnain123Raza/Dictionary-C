#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "DynamicArray.h"

typedef struct SinglyLinkedListNode {
    DynamicArray *definition;

    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

typedef SinglyLinkedListNode Definitions;

/* Constructor and Destructor */

Definitions *createDefinitions(char *definition);
void destroyDefinitions(Definitions *definitions);

/* Definitions Operations */

int pushDefinitionDefinitions(Definitions *definitions, char *definition);
int removeDefinitionDefinitions(Definitions *definitions, unsigned int definitionIndex);
Definition *getDefinitionDefinitions(Definitions *definitions, unsigned int definitionIndex);

#endif