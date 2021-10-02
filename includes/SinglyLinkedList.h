#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "DynamicArray.h"

#include <stdlib.h>

typedef struct SinglyLinkedListNode {
    Definition *definition;

    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

typedef SinglyLinkedListNode Definitions;

/* Constructor and Destructor */

Definitions *createDefinitions(char *definition);
void destroyDefinitions(Definitions *definitions);

/* Definitions Operations */

int pushDefinitionDefinitions(Definitions *definitions, char *definition);
Definitions *removeDefinitionDefinitions(Definitions *definitions, unsigned int definitionIndex, unsigned int index);
Definition *getDefinitionDefinitions(Definitions *definitions, unsigned int definitionIndex, unsigned int index);

#endif