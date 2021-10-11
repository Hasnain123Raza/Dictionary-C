#include "WordsArray.h"

/* Constructor and Destructor */

Word *createWord(char *word, Definitions *definitions)
{
    Word *newWord = malloc(sizeof(Word));
    if (!newWord)
        return NULL;
    
    memset(newWord->word, '\0', KEY_WORD_LENGTH + 1);
    strncpy(newWord->word, word, KEY_WORD_LENGTH);

    newWord->definitions = definitions;

    return newWord;
}

void destroyWord(Word *word)
{
    destroyDefinitions(word->definitions);
    free(word);
}

WordsArray *createWordsArray(Word *word)
{
    WordsArray *wordsArray = malloc(sizeof(WordsArray));
    if (!wordsArray)
        return NULL;
    
    wordsArray->capacity = INITIAL_WORDS_CAPACITY;
    wordsArray->length = 0;

    Word **wordsMemory = calloc(INITIAL_WORDS_CAPACITY, sizeof(Word *));
    if (!wordsMemory)
    {
        free(wordsArray);
        return NULL;
    }

    wordsArray->words = wordsMemory;

    if (!appendWordsArray(wordsArray, word))
    {
        free(wordsArray);
        free(wordsMemory);
        return NULL;
    }

    return wordsArray;
}

void destroyWordsArray(WordsArray *wordsArray)
{
    for (int index = 0; index < wordsArray->length; index++)
        destroyWord(wordsArray->words[index]);

    free(wordsArray->words);
    free(wordsArray);
}

/* Definition Operations */

int growWordsArray(WordsArray *wordsArray)
{
    unsigned int newCapacity = wordsArray->capacity * 2;
    
    Word **newData = calloc(newCapacity, sizeof(Word *));

    if (!newData)
    {
        free(newData);
        return 0;
    }

    memcpy(newData, wordsArray->words, wordsArray->capacity * sizeof(Word *));
    free(wordsArray->words);
    wordsArray->words = newData;
    wordsArray->capacity = newCapacity;
    
    return 1;
}

int appendWordsArray(WordsArray *wordsArray, Word *word)
{
    unsigned int newLength = wordsArray->length + 1;
    if (wordsArray->capacity < newLength)
        if (!growWordsArray(wordsArray))
            return 0;

    wordsArray->words[wordsArray->length] = word;
    wordsArray->length = newLength;

    return 1;
}