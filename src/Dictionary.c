#include "BinarySearchTree.h"

#include <stdio.h>
#include <string.h>

#define PREFIX_BUFFER_SIZE 256
#define CHARS_PER_READ 16

DynamicArray *readInput();

int processCommand(Dictionary *dictionary, DynamicArray* input);
int processInsert(Dictionary *dictionary, DynamicArray* input);
int processRemove(Dictionary *dictionary, DynamicArray* input);
int processRemoveDefinition(Dictionary *dictionary, DynamicArray* input);
int processSearch(Dictionary *dictionary, DynamicArray* input);
int processSearchDefinition(Dictionary *dictionary, DynamicArray* input);

int main(void)
{
    Dictionary *dictionary = createDictionary("Life", createDefinitions(createDefinition("The condition that distinguishes animals and plants from inorganic matter")));
    insertDefinitionDictionary(dictionary, "Life", createDefinition("The existence of an individual human being or animal"));
    insertDefinitionDictionary(dictionary, "Life", createDefinition("The period between the birth and death of a living thing, especially a human being"));

    insertWordDictionary(dictionary, "Bank", createDefinitions(createDefinition("The land alongside or sloping down to a river or lake")));
    insertDefinitionDictionary(dictionary, "Bank", createDefinition("A slope, mass, or mound of a particular substance"));
    insertDefinitionDictionary(dictionary, "Bank", createDefinition("A financial establishment"));

    insertWordDictionary(dictionary, "Station", createDefinitions(createDefinition("A regular stopping place on a public transportation route")));
    insertDefinitionDictionary(dictionary, "Station", createDefinition("A place or building where a specified activity or service is based"));

    insertWordDictionary(dictionary, "Fire", createDefinitions(createDefinition("Combustion or burning")));
    insertDefinitionDictionary(dictionary, "Fire", createDefinition("A burning sensation in the body"));
    insertDefinitionDictionary(dictionary, "Fire", createDefinition("Discharge a gun or other weapon"));

    insertWordDictionary(dictionary, "Free", createDefinitions(createDefinition("Not under the control or in the power of another")));
    insertDefinitionDictionary(dictionary, "Free", createDefinition("Not or no longer confined or imprisoned"));
    insertDefinitionDictionary(dictionary, "Free", createDefinition("Without cost or payment"));

    insertWordDictionary(dictionary, "Stream", createDefinitions(createDefinition("A small, narrow river")));
    insertDefinitionDictionary(dictionary, "Stream", createDefinition("A continuous flow of liquid, air, or gas"));
    insertDefinitionDictionary(dictionary, "Stream", createDefinition("Run or flow in a continuous current in a specified direction"));

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
        DynamicArray *input = readInput();
        
        if (processCommand(dictionary, input))
            printf("\n");
            
        destroyDefinition(input);
    }

    return 0;
}

DynamicArray *readInput()
{
    char inputBuffer[CHARS_PER_READ];
    DynamicArray *input = createDefinition("");

    while (fgets(inputBuffer, CHARS_PER_READ, stdin))
    {
        appendDefinition(input, inputBuffer);

        if (strlen(inputBuffer) + 1 < CHARS_PER_READ || inputBuffer[CHARS_PER_READ - 2] == '\n') /* ...\n\0 */
            break;
    }

    input->value[input->length - 1] = '\0';
    input->length--;

    return input;
}