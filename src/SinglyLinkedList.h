#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "DynamicArray.h"

typedef struct SinglyLinkedListNode {
    DynamicArray *definition;

    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

typedef SinglyLinkedListNode Definitions;

/* Constructor and Destructor */

SinglyLinkedListNode *createSinglyLinkedList(char *definition);
void destroySinglyLinkedList(SinglyLinkedListNode *singlyLinkedList);

/* SinglyLinkedList Operations */



#endif