#ifndef COMMANDS_H
#define COMMANDS_H

#include "DynamicArray.h"
#include "SinglyLinkedList.h"
#include "BinarySearchTree.h"

#include <regex.h>
#include <stdio.h>
#include <string.h>

#define PREFIX_BUFFER_SIZE 256

int processCommand(Dictionary *dictionary, DynamicArray* input);
int processInsert(Dictionary *dictionary, DynamicArray* input);
int processRemove(Dictionary *dictionary, DynamicArray* input);
int processRemoveDefinition(Dictionary *dictionary, DynamicArray* input);
int processSearch(Dictionary *dictionary, DynamicArray* input);
int processSearchDefinition(Dictionary *dictionary, DynamicArray* input);

#endif