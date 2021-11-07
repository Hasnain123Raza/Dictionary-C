#ifndef WORDSARRAY_H
#define WORDSARRAY_H

#include "SinglyLinkedList.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_WORDS_CAPACITY 64
#define KEY_WORD_LENGTH 24

typedef struct {
    char word[KEY_WORD_LENGTH + 1];
    Definitions *definitions;
} Word;

typedef struct {
    unsigned int capacity;
    unsigned int length;

    Word **words;
} WordsArray;

/* Constructor and Destructor */

Word *createWord(char *word, Definitions *definitions);
void destroyWord(Word *word);
WordsArray *createWordsArray(Word *word);
void destroyWordsArray(WordsArray *wordsArray);

/* Definition Operations */

int growWordsArray(WordsArray *wordsArray);
int appendWordsArray(WordsArray *wordsArray, Word *word);

#endif