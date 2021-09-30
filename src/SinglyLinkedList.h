#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "DynamicArray.h"

typedef struct SinglyLinkedListNode {
    DynamicArray *definition;

    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

#endif