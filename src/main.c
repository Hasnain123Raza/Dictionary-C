#include "BinarySearchTree.h"
#include "Commands.h"
#include "Downloader.h"
#include "FileUtility.h"
#include "WordsArray.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
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
            exit(EXIT_FAILURE);
        }

        printf("Saving words in dictionary.txt\n");
        if (!writeWordsToFile(wordsArray, "dictionary.txt"))
        {
            printf("Unable to write words to file\n");
            destroyWordsArray(wordsArray);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Reading file\n");
        wordsArray = readWordsFromFile("dictionary.txt");
        if (!wordsArray)
        {
            printf("Unable to read words from file\n");
            exit(EXIT_FAILURE);
        }
    }

    Dictionary *dictionary = buildDictionaryFromWordsArray(wordsArray);
    if (!dictionary)
    {
        printf("Unable to build tree from words array\n");
        exit(EXIT_FAILURE);
    }
    free(wordsArray->words);
    free(wordsArray);

    printf("\n");
    printf("WELCOME TO DICTIONARY PROGRAM\n");
    printf("\n");
    printf("Use the following commands to interact:\n");
    printf("i to insert\n");
    printf("r to remove\n");
    printf("s to search\n");
    printf("p to print\n");
    printf("q to quit\n");
    printf("\n");

    while (1)
    {
        DynamicArray *input = readInput(stdin);
        
        if (processCommand(dictionary, input))
            printf("\n");
            
        destroyDefinition(input);
    }

    destroyDictionary(dictionary);

    return 0;
}