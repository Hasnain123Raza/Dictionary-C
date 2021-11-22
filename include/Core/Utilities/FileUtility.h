#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include "WordsArray.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARS_PER_READ 16

int writeWordsToFile(WordsArray *wordsArray, char *fileName);
DynamicArray *readInput(FILE *stream);
WordsArray *readWordsFromFile(char *fileName);

#endif