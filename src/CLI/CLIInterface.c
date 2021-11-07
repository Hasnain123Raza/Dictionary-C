#include "CLIInterface.h"

static void printWelcomeMessage();

void handleInputCLI(Dictionary *dictionary, APPLICATION_STATE* applicationState)
{
    static int firstTime = 1;
    if (firstTime)
    {
        printWelcomeMessage();
        firstTime = 0;
    }

    DynamicArray *input = readInput(stdin);
        
    if (processCommand(dictionary, applicationState, input))
        printf("\n");
        
    destroyDefinition(input);
}

static void printWelcomeMessage()
{
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
}