#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include "WordsArray.h"

#include <stdio.h>

int writeWordsToFile(WordsArray *wordsArray, char *fileName);
WordsArray *readWordsFromFile(char *fileName);

#endif