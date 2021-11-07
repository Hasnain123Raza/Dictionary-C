#include <stdio.h>

#include "Initializer.h"
#include "Commands.h"

int main(int argc, char *argv[])
{
    Dictionary *dictionary = initialize(argc, argv);
    if (!dictionary)
    {
        exit(EXIT_FAILURE);
    }

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

    exit(EXIT_SUCCESS);
}