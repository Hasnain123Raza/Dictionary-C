#include "Commands.h"

static int processInsert(Dictionary **dictionary, DynamicArray* input);
static int processInsertWithSpaces(Dictionary **dictionary, DynamicArray* input);
static int processRemove(Dictionary **dictionary, DynamicArray* input);
static int processRemoveWithSpaces(Dictionary **dictionary, DynamicArray* input);
static int processRemoveDefinition(Dictionary **dictionary, DynamicArray* input);
static int processRemoveDefinitionWithSpaces(Dictionary **dictionary, DynamicArray* input);
static int processSearch(Dictionary **dictionary, DynamicArray* input);
static int processSearchWithSpaces(Dictionary **dictionary, DynamicArray* input);
static int processSearchDefinition(Dictionary **dictionary, DynamicArray* input);
static int processSearchDefinitionWithSpace(Dictionary **dictionary, DynamicArray* input);

int processCommand(Dictionary **dictionary, APPLICATION_STATE* applicationState, DynamicArray* input)
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
            printDictionary(*dictionary, "", 0);
            return 1;

        case 'g':
            applicationState->mode = MODE_GUI;
            return 1;

        case 'q':
            printf("Goodbye!\n");
            applicationState->done = 1;
            return 1;

        default:
            printf("Invalid command selector, please try again\n");
            return 0;
        }
}

static int processInsert(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(i) ([a-zA-Z]+) (.+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for insert command\n");
        return 0;
    }

    int totalMatches = 4;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processInsertWithSpaces(dictionary, input);
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

    if (searchWordDictionary(*dictionary, word))
        insertDefinitionDictionary(*dictionary, word, createDefinition(definition));
    else
        insertWordDictionary(*dictionary, word, createDefinitions(createDefinition(definition)));

    return 1;
}

static int processInsertWithSpaces(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(i) \"([^\"]+)\" (.+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for insert with spaces command\n");
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

    if (searchWordDictionary(*dictionary, word))
        insertDefinitionDictionary(*dictionary, word, createDefinition(definition));
    else
        insertWordDictionary(*dictionary, word, createDefinitions(createDefinition(definition)));

    return 1;
}

static int processRemove(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(r) ([a-zA-Z]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for remove command\n");
        return 0;
    }

    int totalMatches = 3;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processRemoveWithSpaces(dictionary, input);
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    regfree(&regexCompiled);

    *dictionary = removeWordDictionary(*dictionary, word);

    return 1;
}

static int processRemoveWithSpaces(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(r) \"([^\"]+)\"$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for remove with spaces command\n");
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

    *dictionary = removeWordDictionary(*dictionary, word);

    return 1;
}

static int processRemoveDefinition(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(r) ([a-zA-Z]+) ([0-9]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for remove definition command\n");
        return 0;
    }

    int totalMatches = 4;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processRemoveDefinitionWithSpaces(dictionary, input);
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

    *dictionary = removeDefinitionDictionary(*dictionary, word, atoi(definitionIndex) - 1);

    return 1;
}

static int processRemoveDefinitionWithSpaces(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(r) \"([^\"]+)\" ([0-9]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for remove definition with spaces command\n");
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

    *dictionary = removeDefinitionDictionary(*dictionary, word, atoi(definitionIndex) - 1);

    return 1;
}

static int processSearch(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(s) ([a-zA-Z]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for search command\n");
        return 0;
    }

    int totalMatches = 3;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processSearchWithSpaces(dictionary, input);
    }

    int wordLength = matches[2].rm_eo - matches[2].rm_so;
    char word[wordLength + 1];
    memset(word, '\0', wordLength + 1);
    strncpy(word, input->value + matches[2].rm_so, wordLength);

    regfree(&regexCompiled);

    Definitions *definitions = searchWordDictionary(*dictionary, word);
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

static int processSearchWithSpaces(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(s) \"([^\"]+)\"$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for search with spaces command\n");
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

    Definitions *definitions = searchWordDictionary(*dictionary, word);
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

static int processSearchDefinition(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(s) ([a-zA-Z]+) ([0-9]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for search definition command\n");
        return 0;
    }

    int totalMatches = 4;
    regmatch_t matches[totalMatches];

    if (regexec(&regexCompiled, input->value, totalMatches, matches, 0))
    {
        regfree(&regexCompiled);
        return processSearchDefinitionWithSpace(dictionary, input);
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

    Definition* definition = searchDefinitionDictionary(*dictionary, word, atoi(definitionIndex) - 1);
    if (definition)
        printf("%s\n", definition->value);
    else
        printf("Unable to find %s in the dictionary\n", word);

    return 1;
}

static int processSearchDefinitionWithSpace(Dictionary **dictionary, DynamicArray* input)
{
    char regexPattern[] = "^(s) \"([^\"]+)\" ([0-9]+)$";

    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Unable to compile regular expression for search definition with spaces command\n");
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

    Definition* definition = searchDefinitionDictionary(*dictionary, word, atoi(definitionIndex) - 1);
    if (definition)
        printf("%s\n", definition->value);
    else
        printf("Unable to find %s in the dictionary\n", word);

    return 1;
}