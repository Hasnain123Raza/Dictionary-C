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



#endif