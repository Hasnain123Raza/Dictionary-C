#include "FileUtility.h"

int writeWordsToFile(WordsArray *wordsArray, char *fileName)
{
    FILE *dictionaryFile = fopen(fileName, "w");
    if (!dictionaryFile)
        return 0;

    for (int index = 0; index < wordsArray->length; index++)
	{
		fputs(wordsArray->words[index]->word, dictionaryFile);
		fputc('\n', dictionaryFile);

		Definitions *definitions = wordsArray->words[index]->definitions;
		while (definitions)
		{
			fputs(definitions->definition->value, dictionaryFile);
			fputc('\n', dictionaryFile);

			definitions = definitions->next;
		}

		fputc('\n', dictionaryFile);
	}

    return 1;
}

WordsArray *readWordsFromFile(char *fileName)
{
    
}