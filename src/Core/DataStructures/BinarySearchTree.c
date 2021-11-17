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



static Dictionary *dictionaryFromWordsArray(WordsArray *wordsArray, int start, int end)
{
    if (start > end)
        return NULL;
    
    int mid = start + (end - start)/2;
    Dictionary *dictionary = createDictionary(wordsArray->words[mid]->word, wordsArray->words[mid]->definitions);

    dictionary->left = dictionaryFromWordsArray(wordsArray, start, mid - 1);
    dictionary->right = dictionaryFromWordsArray(wordsArray, mid + 1, end);

    return dictionary;
}

Dictionary *buildDictionaryFromWordsArray(WordsArray *wordsArray)
{
    Dictionary* dictionary = dictionaryFromWordsArray(wordsArray, 0, wordsArray->length - 1);
    return dictionary;
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

    return node->definitions;
}

Definition *searchDefinitionDictionary(Dictionary *dictionary, char *word, unsigned int definitionIndex)
{
    Dictionary *node = searchNodeDictionary(dictionary, word);
    if (!node)
        return NULL;

    return getDefinitionDefinitions(node->definitions, definitionIndex, 0);
}

static Dictionary *matchNode(Dictionary *dictionary, char *prefix)
{
    if (dictionary == NULL)
        return NULL;

    int comparisonResult = strncmp(prefix, dictionary->word, strlen(prefix));
    if (comparisonResult < 0)
        return matchNode(dictionary->left, prefix);
    else if (comparisonResult > 0)
        return matchNode(dictionary->right, prefix);
    else
        return dictionary;
}

static void grabWords(Dictionary *dictionary, char *prefix, char *words[], unsigned int maxWords, unsigned int *count)
{
    if (dictionary == NULL)
        return;

    if (*count >= maxWords)
        return;

    Dictionary *node = matchNode(dictionary, prefix);
    if (!node)
        return;

    words[*count] = node->word;
    (*count)++;

    grabWords(node->left, prefix, words, maxWords, count);
    grabWords(node->right, prefix, words, maxWords, count);
}

unsigned int getMatchesDictionary(Dictionary *dictionary, char *prefix, char *words[], unsigned int maxWords)
{
    unsigned int count = 0;
    grabWords(dictionary, prefix, words, maxWords, &count);
    return count;
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