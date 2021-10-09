#include "DynamicList.h"

/* Constructor and Destructor */

Definition *createDefinition(char *definition)
{
    Definition *newDefinition = malloc(sizeof(Definition));
    if (!newDefinition)
        return NULL;
    
    newDefinition->capacity = INITIAL_DEFINITION_CAPACITY;
    newDefinition->length = 0;

    char *definitionMemory = calloc(INITIAL_DEFINITION_CAPACITY, sizeof(char));
    if (!definitionMemory)
    {
        free(newDefinition);
        return NULL;
    }

    memset(definitionMemory, '\0', INITIAL_DEFINITION_CAPACITY);
    newDefinition->value = definitionMemory;

    if (!appendDefinition(newDefinition, definition))
    {
        free(newDefinition);
        free(definitionMemory);
        return NULL;
    }

    return newDefinition;
}

void destroyDefinition(Definition *definition)
{
    free(definition->value);
    free(definition);
}

/* Definition Operations */

int growDefinition(Definition *definition)
{
    unsigned int newCapacity = definition->capacity * 2;
    
    char *newData = calloc(newCapacity, sizeof(char));

    if (!newData)
    {
        free(newData);
        return 0;
    }
    memset(newData, '\0', newCapacity);

    memcpy(newData, definition->value, definition->capacity);
    free(definition->value);
    definition->value = newData;
    definition->capacity = newCapacity;

    return 1;
}

int appendDefinition(Definition *definition, char *toAppend)
{
    unsigned int newLength = definition->length + strlen(toAppend);
    while (definition->capacity < newLength + 1)    /* accounting for the NULL character */
        if (!growDefinition(definition))
            return 0;
    
    strcat(definition->value, toAppend);
    definition->length = newLength;

    return 1;
}
