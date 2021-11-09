#ifndef COMMANDS_H
#define COMMANDS_H

#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "DynamicArray.h"
#include "SinglyLinkedList.h"
#include "BinarySearchTree.h"
#include "Common.h"

#define PREFIX_BUFFER_SIZE 256

int processCommand(Dictionary **dictionary, APPLICATION_STATE* applicationState, DynamicArray* input);

#endif