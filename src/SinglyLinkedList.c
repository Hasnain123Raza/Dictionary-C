#include "SinglyLinkedList.h"

/* Constructor and Destructor */

Definitions *createDefinitions(char *definition)
{
    Definitions *definitions = malloc(sizeof(Definitions));
    if (!definitions)
        return NULL;
    
    Definition *newDefinition = createDefinition(definition);
    if (!newDefinition)
    {
        free(definitions);
        return NULL;
    }
    definitions->definition = newDefinition;

    definitions->next = NULL;

    return definitions;
}

void destroyDefinitions(Definitions *definitions)
{
    if (definitions->next)
        destroyDefinitions(definitions->next);
    
    destroyDefinition(definitions->definition);
    free(definitions);
}

/* Definitions Operations */

int pushDefinitionDefinitions(Definitions *definitions, char *definition)
{
    if (definitions->next)
        return pushDefinitionDefinitions(definitions->next, definition);
    else
    {
        Definitions *newDefinitions = createDefinitions(definition);
        if (!newDefinitions)
            return 0;
        
        definitions->next = newDefinitions;

        return 1;
    }
}

Definitions *removeDefinitionDefinitions(Definitions *definitions, unsigned int definitionIndex, unsigned int index)
{
    if (definitions == NULL)
        return definitions;

    if (index != definitionIndex)
        definitions->next = removeDefinitionDefinitions(definitions->next, definitionIndex, ++index);
    else
    {
        Definitions *nextNode = definitions->next;
        destroyDefinition(definitions->definition);
        free(definitions);
        return nextNode;
    }

    return definitions;
}

Definition *getDefinitionDefinitions(Definitions *definitions, unsigned int definitionIndex, unsigned int index)
{
    if (definitions == NULL)
        return NULL;
    
    if (index != definitionIndex)
        return getDefinitionDefinitions(definitions->next, definitionIndex, ++index);
    else
        return definitions->definition;
}