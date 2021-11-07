#include "Initializer.h"

Dictionary *initialize(int argc, char *argv[])
{
    if (argc > 2)
        printf("Too many arguments, ignoring some\n");

    int skip = 0;

    if (argc > 1)
        skip = atoi(argv[1]);
    
    WordsArray *wordsArray = NULL;

    if (skip > 0)
    {
        printf("Downloading words\n");
        wordsArray = downloadWords(skip);
        if (!wordsArray)
        {
            printf("Unable to download words\n");
            return NULL;
        }

        printf("Saving words in dictionary.txt\n");
        if (!writeWordsToFile(wordsArray, "dictionary.txt"))
        {
            printf("Unable to write words to file\n");
            destroyWordsArray(wordsArray);
            return NULL;
        }
    }
    else
    {
        printf("Reading file\n");
        wordsArray = readWordsFromFile("dictionary.txt");
        if (!wordsArray)
        {
            printf("Unable to read words from file\n");
            return NULL;
        }
    }

    Dictionary *dictionary = buildDictionaryFromWordsArray(wordsArray);
    if (!dictionary)
    {
        printf("Unable to build tree from words array\n");
        return NULL;
    }
    free(wordsArray->words);
    free(wordsArray);

    return dictionary;
}