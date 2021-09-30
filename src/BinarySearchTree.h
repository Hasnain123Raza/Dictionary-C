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

#endif