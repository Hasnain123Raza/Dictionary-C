#include "BinarySearchTree.h"

#include <regex.h>
#include <stdio.h>
#include <string.h>

#define PREFIX_BUFFER_SIZE 256
#define CHARS_PER_READ 16

void printDictionary(Dictionary *dictionary, char *prefix, int isLeft);
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

void printDictionary(Dictionary *dictionary, char *prefix, int isLeft)
{
    if (dictionary == NULL)
		return;

	printf("%s", prefix);
	printf(isLeft ? "├──" : "└──");
	printf("%s", dictionary->word);
	printf("\n");
	
	char newPrefix[PREFIX_BUFFER_SIZE] = {};
	strcat(newPrefix, prefix);
	strcat(newPrefix,  (isLeft ? "│   " : "    "));

    Definitions* definitions = dictionary->definitions;
    int counter = 1;
    while (definitions)
    {
        printf("%s", newPrefix);
        printf("%d: %s\n", counter, definitions->definition->value);
        counter++;
        definitions = definitions->next;
    }

	printDictionary(dictionary->left, newPrefix, 1);
	printDictionary(dictionary->right, newPrefix, 0);
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

int processCommand(Dictionary *dictionary, DynamicArray* input)
{
    if (strlen(input->value) == 0)
        {
            printf("No input was received, please try again\n");
            return 0;
        }

        char commandSelector = input->value[0];
        switch (commandSelector)
        {
        case 'i':
            return processInsert(dictionary, input);

        case 'r':
            return processRemove(dictionary, input);
        
        case 's':
            return processSearch(dictionary, input);

        case 'p':
            printDictionary(dictionary, "", 0);
            return 1;

        case 'q':
            printf("Goodbye!\n");
            exit(EXIT_SUCCESS);

        default:
            printf("Invalid command selector, please try again\n");
            return 0;
        }
}

int processInsert(Dictionary *dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(i) ([a-zA-Z]+) (.+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        printf("Unable to compile regular expression for insert command\n");
        return 0;
    }

    int totalMatches = 4;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        printf("Unable to parse input, please try again\n");
        return 0;
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    int definitionLength = matches[3].rm_eo - matches[3].rm_so;
    char definition[definitionLength + 1];
    memset(definition, '\0', definitionLength + 1);
    strncpy(definition, input->value + matches[3].rm_so, definitionLength);

    regfree(&regexCompiled);

    if (searchWordDictionary(dictionary, word))
        insertDefinitionDictionary(dictionary, word, createDefinition(definition));
    else
        insertWordDictionary(dictionary, word, createDefinitions(createDefinition(definition)));

    return 1;
}

int processRemove(Dictionary *dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(r) ([a-zA-Z]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        printf("Unable to compile regular expression for remove command\n");
        return 0;
    }

    int totalMatches = 3;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processRemoveDefinition(dictionary, input);
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    regfree(&regexCompiled);

    dictionary = removeWordDictionary(dictionary, word);

    return 1;
}

int processRemoveDefinition(Dictionary *dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(r) ([a-zA-Z]+) ([0-9]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        printf("Unable to compile regular expression for remove command\n");
        return 0;
    }

    int totalMatches = 4;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        printf("Unable to parse input, please try again\n");
        return 0;
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    int definitionIndexLength = matches[3].rm_eo - matches[3].rm_so;
    char definitionIndex[definitionIndexLength + 1];
    memset(definitionIndex, '\0', definitionIndexLength + 1);
    strncpy(definitionIndex, input->value + matches[3].rm_so, definitionIndexLength);
    
    regfree(&regexCompiled);

    dictionary = removeDefinitionDictionary(dictionary, word, atoi(definitionIndex) - 1);

    return 1;
}

int processSearch(Dictionary *dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(s) ([a-zA-Z]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        printf("Unable to compile regular expression for remove command\n");
        return 0;
    }

    int totalMatches = 3;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processSearchDefinition(dictionary, input);
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    regfree(&regexCompiled);

    Definitions *definitions = searchWordDictionary(dictionary, word);
    if (definitions)
    {
        int counter = 1;
        while (definitions)
        {
            printf("%d %s\n", counter, definitions->definition->value);
            definitions = definitions->next;
            counter++;
        }
    }
    else
        printf("Unable to find %s in the dictionary\n", word);

    return 1;
}

int processSearchDefinition(Dictionary *dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(s) ([a-zA-Z]+) ([0-9]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        printf("Unable to compile regular expression for remove command\n");
        return 0;
    }

    int totalMatches = 4;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        printf("Unable to parse input, please try again\n");
        return 0;
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    int definitionIndexLength = matches[3].rm_eo - matches[3].rm_so;
    char definitionIndex[definitionIndexLength + 1];
    memset(definitionIndex, '\0', definitionIndexLength + 1);
    strncpy(definitionIndex, input->value + matches[3].rm_so, definitionIndexLength);
    
    regfree(&regexCompiled);

    Definition* definition = searchDefinitionDictionary(dictionary, word, atoi(definitionIndex) - 1);
    if (definition)
        printf("%s\n", definition->value);
    else
        printf("Unable to find %s in the dictionary\n", word);

    return 1;
}