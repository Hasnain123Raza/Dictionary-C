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

#endif