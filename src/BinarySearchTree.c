#include "BinarySearchTree.h"

/* Constructor and Destructor */

Dictionary *createDictionary(char *word, Definitions *definitions)
{
    Dictionary *dictionary = malloc(sizeof(Dictionary));
    if (!dictionary)
        return NULL;

    memset(dictionary->word, '\0', KEY_WORD_LENGTH + 1);
    strncpy(dictionary->word, word, KEY_WORD_LENGTH);

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
    
    destroyDefinitions(dictionary->definitions);
    free(dictionary);
}

/* Dictionary Operations */

static Dictionary *searchNodeDictionary(Dictionary *dictionary, char *word)
{
    if (dictionary == NULL)
        return NULL;

    int comparisonResult = strcmp(word, dictionary->word);

    if (comparisonResult < 0)
        searchNodeDictionary(dictionary->left, word);
    else if (comparisonResult > 0)
        searchNodeDictionary(dictionary->right, word);
    else
        return dictionary;
}

int insertWordDictionary(Dictionary *dictionary, char *word, Definitions *definitions)
{
    int comparisonResult = strcmp(word, dictionary->word);

    if (comparisonResult < 0)
    {
        if (dictionary->left)
            return insertWordDictionary(dictionary->left, word, definitions);
        else
        {
            Dictionary *node = createDictionary(word, definitions);
            if (!node)
                return 0;
            dictionary->left = node;
            return 1;
        }
    }
    else if (comparisonResult > 0)
    {
        if (dictionary->right)
            return insertWordDictionary(dictionary->right, word, definitions);
        else
        {
            Dictionary *node = createDictionary(word, definitions);
            if (!node)
                return 0;
            dictionary->right = node;
            return 1;
        }
    }
    else
        return 0;   /* No Duplicates */
}

int insertDefinitionDictionary(Dictionary *dictionary, char *word, Definition *definition)
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
            destroyDefinitions(dictionary->definitions);
            free(dictionary);
            return childNode;
        }
        else
        {
            destroyDefinitions(dictionary->definitions);
            free(dictionary);
            return NULL;
        }
    }

    return dictionary;
}

Dictionary *removeDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex)
{
    Dictionary *node = searchNodeDictionary(dictionary, word);
    if (node)
        if (node->definitions->next == NULL)
            return removeWordDictionary(dictionary, word);
        else
            node->definitions = removeDefinitionDefinitions(node->definitions, definitionIndex, 0);
    
    return dictionary;
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