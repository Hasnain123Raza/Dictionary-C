#include "BinarySearchTree.h"

/* Constructor and Destructor */

Dictionary *createDictionary(char *word, char *definition)
{
    Dictionary *dictionary = malloc(sizeof(Dictionary));
    if (!dictionary)
        return NULL;

    strncpy(dictionary->word, word, KEY_WORD_LENGTH);

    Definitions *definitions = createDefinitions(definition);
    if (!definitions)
    {
        free(dictionary);
        return NULL;
    }

    dictionary->definitions = definitions;

    dictionary->left = NULL;
    dictionary->right = NULL;

    return dictionary;
}

void destroyDictionary(Dictionary *dictionary)
{
    if (dictionary->left)
        destroyDictionary(dictionary->left);
    
    if (dictionary->right)
        destroyDictionary(dictionary->right);
    
    destroySinglyLinkedList(dictionary->definitions);
    free(dictionary);
}

/* Dictionary Operations */

static Dictionary *searchNodeDictionary(Dictionary *dictionary, char *word)
{
    if (dictionary == NULL)
        return NULL;

    int comparisonResult = strcmp(word, dictionary->word);

    if (comparisonResult < 0)
        searchWordNodeDictionary(dictionary->left, word);
    else if (comparisonResult > 0)
        searchWordNodeDictionary(dictionary->right, word);
    else
        return dictionary;
}

int insertWordDictionary(Dictionary *dictionary, char *word, char *definition)
{
    int comparisonResult = strcmp(word, dictionary->word);

    if (comparisonResult < 0)
    {
        if (dictionary->left)
            return insertWordDictionary(dictionary->left, word, definition);
        else
        {
            Dictionary *node = createDictionary(word, definition);
            if (!node)
                return 0;
            dictionary->left = node;
            return 1;
        }
    }
    else if (comparisonResult > 0)
    {
        if (dictionary->right)
            return insertWordDictionary(dictionary->right, word, definition);
        else
        {
            Dictionary *node = createDictionary(word, definition);
            if (!node)
                return 0;
            dictionary->right = node;
            return 1;
        }
    }
    else
        return 0;   /* No Duplicates */
}

int insertDefinitionDictionary(Dictionary *dictionary, char *word, char *definition)
{
    Dictionary *node = searchNodeDictionary(dictionary, word);
    if (!node)
        return 0;

    if (!pushDefinitionDefinitions(node->definitions, definition))
        return 0;

    return 1;
}

Dictionary *removeWordDictionary(Dictionary *dictionary, char *word)
{
    if (dictionary == NULL)
        return dictionary;

    int comparisonResult = strcmp(word, dictionary->word);

    if (comparisonResult < 0)
        dictionary->left = removeWordDictionary(dictionary->left, word);
    else if (comparisonResult > 0)
        dictionary->right = removeWordDictionary(dictionary->right, word);
    else
    {
        if (dictionary->left && dictionary->right)
        {
            Dictionary *maximumValueNode = dictionary->left;
            while (maximumValueNode->right)
                maximumValueNode = maximumValueNode->right;
            
            strcpy(dictionary->word, maximumValueNode->word);
            Definitions *temporary = dictionary->definitions;
            dictionary->definitions = maximumValueNode->definitions;
            maximumValueNode->definitions = temporary;

            dictionary->left = removeWordDictionary(dictionary->left, maximumValueNode->word);
        }
        else if (dictionary->left || dictionary->right)
        {
            Dictionary *childNode = dictionary->left ? dictionary->left : dictionary->right;
            destroyDictionary(dictionary);
            return childNode;
        }
        else
        {
            destroyDictionary(dictionary);
            return NULL;
        }
    }

    return dictionary;
}

int removeDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex)
{
    Dictionary *node = searchNodeDictionary(dictionary, word);
    if (!node)
        return 0;

    if (!removeDefinitionDefinitions(node->definitions, definitionIndex, 0))
        return 0;

    return 1;
}

Definitions *searchWordDictionary(Dictionary *dictionary, char *word)
{
    Dictionary *node = searchNodeDictionary(dictionary, word);
    if (!node)
        return NULL;

    return dictionary->definitions;
}

Definition *searchDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex)
{
    Dictionary *node = searchNodeDictionary(dictionary, word);
    if (!node)
        return NULL;

    return getDefinitionDefinitions(dictionary->definitions, definitionIndex, 0);
}