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

DynamicArray *readInput(FILE *stream)
{
	char inputBuffer[CHARS_PER_READ] = {};
	DynamicArray *input = createDefinition("");
	if (!input)
	{
		printf("Unable to allocate space for input\n");
		return NULL;
	}

	while (fgets(inputBuffer, CHARS_PER_READ, stream))
	{
		if (!appendDefinition(input, inputBuffer))
		{
			printf("Unable to allocate space for input\n");
			destroyDefinition(input);
			return NULL;
		}

		if (inputBuffer[strlen(inputBuffer) - 1] == '\n')
			break;
	}

	if (input->length == 0) /* EOF indicated with a length of -1 */
	{
		input->length = -1;
		return input;
	}

	input->value[input->length - 1] = '\0';
	input->length--;

	return input;
}

WordsArray *readWordsFromFile(char *fileName)
{
    FILE *dictionaryFile = fopen(fileName, "r");
	if (!dictionaryFile)
	{
		printf("Unable to read dictionary file: %s\n", fileName);
		return NULL;
	}

	WordsArray *wordsArray = NULL;

	while (1)
	{
		int isEOF = 0;
		DynamicArray *wordInput = readInput(dictionaryFile);
		if (!wordInput)
		{
			printf("Unable to allocate space for word input while reading dictionary file: %s\n", fileName);

			if (wordsArray)
				destroyWordsArray(wordsArray);
			return NULL;
		}

		Definitions *definitions = NULL;
		while (1)
		{
			Definition *definition = readInput(dictionaryFile);
			if (!definition)
			{
				printf("Unable to allocate space for definition while reading dictionary file: %s\n", fileName);
				if (definitions)
					destroyDefinitions(definitions);
				if (wordsArray)
					destroyWordsArray(wordsArray);
				destroyDefinition(wordInput);

				return NULL; 
			}

			if (definition->length == -1) /* EOF */
			{
				destroyDefinition(definition);
				isEOF = 1;
				break;
			}

			if (definition->length == 0) /* Definitions for the current words have all been parsed */
			{
				destroyDefinition(definition);
				break;
			}

			if (!definitions)
			{
				definitions = createDefinitions(definition);
				if (!definitions)
				{
					printf("Unable to allocate space for definitions while reading dictionary file: %s\n", fileName);
					destroyDefinition(definition);
					if (wordsArray)
						destroyWordsArray(wordsArray);
					destroyDefinition(wordInput);

					return NULL;
				}
			}
			else
			{
				if (!pushDefinitionDefinitions(definitions, definition))
				{
					printf("Unable to allocate space for definitions while reading dictionary file: %s\n", fileName);
					destroyDefinition(definition);
					destroyDefinitions(definitions);
					if (wordsArray)
						destroyWordsArray(wordsArray);
					destroyDefinition(wordInput);

					return NULL;
				}
			}
		}

		if (wordInput->length > KEY_WORD_LENGTH) /*Only read KEY_WORD_LENGTH characters */
			wordInput->value[KEY_WORD_LENGTH] = '\0';

		Word *word = createWord(wordInput->value, definitions);
		if (!word)
		{
			printf("Unable to allocate space for word while reading dictionary file: %s\n", fileName);
			if (definitions)
				destroyDefinitions(definitions);
			if (wordsArray)
				destroyWordsArray(wordsArray);
			destroyDefinition(wordInput);
			return NULL;
		}

		if (!wordsArray)
		{
			wordsArray = createWordsArray(word);
			if (!wordsArray)
			{
				printf("Unable to allocate space for words array while reading dictionary file: %s\n", fileName);
				destroyWord(word);
				if (definitions)
					destroyDefinitions(definitions);
				if (wordsArray)
					destroyWordsArray(wordsArray);
				destroyDefinition(wordInput);
				return NULL;
			}
		}
		else
		{
			if (!appendWordsArray(wordsArray, word))
			{
				printf("Unable to allocate space for words array while reading dictionary file: %s\n", fileName);
				destroyWord(word);
				if (definitions)
					destroyDefinitions(definitions);
				if (wordsArray)
					destroyWordsArray(wordsArray);
				destroyDefinition(wordInput);
				return NULL;
			}
		}

		destroyDefinition(wordInput);
		if (isEOF)
			return wordsArray;
	}
}