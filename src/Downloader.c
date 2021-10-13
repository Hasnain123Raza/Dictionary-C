#include "Downloader.h"

static int scrapeWords(WordsArray **wordsArray, TidyNode *bodyNode, int skip, int *skipCounter);
static int scrapeNextWordsURL(TidyBuffer *wordsURLBuffer, TidyNode *bodyNode);
static Definitions *downloadDefinitions(char *href);
static Definitions *scrapeDefinitions(TidyDoc *definitionsDocument, TidyNode *bodyNode);
static int scrapeDefinitionFromTree(TidyDoc *definitionsDocument, Definition **definition, TidyNode *rootNode);
static int wordsChunkSelector(TidyNode *nodeToSelect);
static int navigationSelector(TidyNode *nodeToSelect);
static int definitionsOutputSelector(TidyNode *nodeToSelect);

WordsArray *downloadWords(int skip)
{
    int skipCounter = 0;
    WordsArray *wordsArray = NULL;

	TidyBuffer wordsURLBuffer = {};
	tidyBufInit(&wordsURLBuffer);

	tidyBufAppend(&wordsURLBuffer, BASE_URL, strlen(BASE_URL));
	tidyBufAppend(&wordsURLBuffer, FIRST_PAGE_URL, strlen(FIRST_PAGE_URL) + 1);

    while (1)
    {
        TidyBuffer wordsDownloadBuffer = {};
		tidyBufInit(&wordsDownloadBuffer);
		if (!downloadHTML(wordsURLBuffer.bp, &wordsDownloadBuffer))
		{
			printf("Unable to download words from %s\n", wordsURLBuffer.bp);
			tidyBufFree(&wordsDownloadBuffer);
			tidyBufFree(&wordsURLBuffer);
			if (wordsArray)
				destroyWordsArray(wordsArray);
			return NULL;
		}

		TidyDoc wordsDocument = tidyCreate();
		if (!loadTidyDocumentFromTidyBuffer(&wordsDocument, &wordsDownloadBuffer))
		{
			printf("Unable to load words document\n");
			tidyRelease(wordsDocument);
			tidyBufFree(&wordsDownloadBuffer);
			tidyBufFree(&wordsURLBuffer);
			if (wordsArray)
				destroyWordsArray(wordsArray);
			return NULL;
		}

		TidyNode bodyNode = tidyGetBody(wordsDocument);
		if (!bodyNode)
		{
			printf("Unable to find body node in words document\n");
			tidyRelease(wordsDocument);
			tidyBufFree(&wordsDownloadBuffer);
			tidyBufFree(&wordsURLBuffer);
			if (wordsArray)
				destroyWordsArray(wordsArray);
			return NULL;
		}
        
        if (!scrapeWords(&wordsArray, &bodyNode, skip, &skipCounter))
        {
            tidyRelease(wordsDocument);
            tidyBufFree(&wordsDownloadBuffer);
            tidyBufFree(&wordsURLBuffer);
	    if (wordsArray)
            	destroyWordsArray(wordsArray);
            return NULL;
        }

        int nextPageAvailable = scrapeNextWordsURL(&wordsURLBuffer, &bodyNode);
        //nextPageAvailable = 0;

        tidyRelease(wordsDocument);
		tidyBufFree(&wordsDownloadBuffer);

		if (!nextPageAvailable)
		{
			tidyBufFree(&wordsURLBuffer);

			return wordsArray;
		}
    }
}

static int scrapeWords(WordsArray **wordsArray, TidyNode *bodyNode, int skip, int *skipCounter)
{
    TidyNode wordsChunkNode;
    if (!searchTidyNode(bodyNode, &wordsChunkNode, wordsChunkSelector))
    {
        printf("Unable to find words chunk node\n");
        return 0;
    }

    TidyNode wordNode = tidyGetChild(wordsChunkNode);
    while (wordNode)
    {
        TidyNode anchorNode = tidyGetChild(wordNode);
        if (anchorNode)
        {
            TidyAttr titleAttribute = tidyAttrGetById(anchorNode, TidyAttr_TITLE);
            TidyAttr hrefAttribute = tidyAttrGetById(anchorNode, TidyAttr_HREF);
            char *titleValue = (char *)tidyAttrValue(titleAttribute);
            char *hrefValue = (char *)tidyAttrValue(hrefAttribute);

            if (titleValue && hrefValue && isalpha(titleValue[0]) && *skipCounter%skip == 0)
            {
                printf("%s\n", titleValue);
                Definitions *definitions = downloadDefinitions(hrefValue);
                if (!definitions)
                {
                    return 0;
                }

                Word* word = createWord(titleValue, definitions);
                if (!word)
                {
                    printf("Unable to allocate space for word\n");
                    return 0;
                }

                if (!(*wordsArray))
                {
                    *wordsArray = createWordsArray(word);
                    if (!(*wordsArray))
                    {
                        printf("Unable to allocate space for words array\n");
                        destroyWord(word);
                        return 0;
                    }
                }
                else
                {
                    if (!appendWordsArray(*wordsArray, word))
                    {
                        printf("Unable to allocate space for words array\n");
                        destroyWord(word);
                        return 0;
                    }
                }
            }

            (*skipCounter)++;
        }

        wordNode = tidyGetNext(wordNode);
    }

    return 1;
}

static int scrapeNextWordsURL(TidyBuffer *wordsURLBuffer, TidyNode *bodyNode)
{
    TidyNode navigationNode;
    if (!searchTidyNode(bodyNode, &navigationNode, navigationSelector))
    {
        printf("Unable to find words chunk node\n");
        return 0;
    }

    TidyNode nextPageNode = tidyGetChild(navigationNode);
    nextPageNode = nextPageNode ? tidyGetNext(nextPageNode) : NULL;
    nextPageNode = nextPageNode ? tidyGetNext(nextPageNode) : NULL;
    if (!nextPageNode)
        return 0;

    TidyAttr hrefAttribute = tidyAttrGetById(nextPageNode, TidyAttr_HREF);
    const char *hrefValue = tidyAttrValue(hrefAttribute);

    tidyBufFree(wordsURLBuffer);
    tidyBufInit(wordsURLBuffer);

    tidyBufAppend(wordsURLBuffer, BASE_URL, strlen(BASE_URL));
    tidyBufAppend(wordsURLBuffer, (char *)hrefValue, strlen(hrefValue) + 1);

    return 1;
}

static Definitions *downloadDefinitions(char *href)
{
    TidyBuffer definitionsURLBuffer = {};
	tidyBufInit(&definitionsURLBuffer);

	tidyBufAppend(&definitionsURLBuffer, BASE_URL, strlen(BASE_URL));
	tidyBufAppend(&definitionsURLBuffer, href, strlen(href) + 1);

	TidyBuffer definitionsDownloadBuffer = {};
	tidyBufInit(&definitionsDownloadBuffer);

	if (!downloadHTML(definitionsURLBuffer.bp, &definitionsDownloadBuffer))
	{
		printf("Unable to download definitions from %s\n", definitionsURLBuffer.bp);
		tidyBufFree(&definitionsDownloadBuffer);
		tidyBufFree(&definitionsURLBuffer);
		return NULL;
	}

	TidyDoc definitionsDocument = tidyCreate();
	if (!loadTidyDocumentFromTidyBuffer(&definitionsDocument, &definitionsDownloadBuffer))
	{
		printf("Unable to load definitions document\n");
		tidyRelease(definitionsDocument);
		tidyBufFree(&definitionsDownloadBuffer);
		tidyBufFree(&definitionsURLBuffer);
		return NULL;
	}

	TidyNode bodyNode = tidyGetBody(definitionsDocument);
	if (!bodyNode)
	{
		printf("Unable to find body node in definitions document\n");
		tidyRelease(definitionsDocument);
		tidyBufFree(&definitionsDownloadBuffer);
		tidyBufFree(&definitionsURLBuffer);
		return NULL;
	}
    
    Definitions *definitions = scrapeDefinitions(&definitionsDocument, &bodyNode);
    if (!definitions)
    {
        printf("Unable to scrape definitions from %s\n", href);
        printf("A placeholder definition will be added automatically\n");
        
        Definition *placeholder = createDefinition("This is a placeholder definition");
        if (!placeholder)
        {
            printf("Unable to allocate space for placeholder definition\n");
            tidyRelease(definitionsDocument);
		    tidyBufFree(&definitionsDownloadBuffer);
		    tidyBufFree(&definitionsURLBuffer);
		    return NULL;
        }

        definitions = createDefinitions(placeholder);
        if (!definitions)
        {
            printf("Unable to allocate space for placeholder definitions\n");
            destroyDefinition(placeholder);
            tidyRelease(definitionsDocument);
		    tidyBufFree(&definitionsDownloadBuffer);
		    tidyBufFree(&definitionsURLBuffer);
		    return NULL;
        }
    }
    
    tidyRelease(definitionsDocument);
	tidyBufFree(&definitionsDownloadBuffer);
	tidyBufFree(&definitionsURLBuffer);

    return definitions;
}

static Definitions *scrapeDefinitions(TidyDoc *definitionsDocument, TidyNode *bodyNode)
{
    Definitions *definitions = NULL;

    TidyNode definitionsOutputNode;
    if (!searchTidyNode(bodyNode, &definitionsOutputNode, definitionsOutputSelector))
    {
        printf("Unable to find definitions output node\n");
        return 0;
    }

	TidyNode definitionsListNode = tidyGetChild(definitionsOutputNode);
	while (definitionsListNode && tidyNodeGetType(definitionsListNode) != TidyNode_Comment)
	{
		if (!strcmp(tidyNodeGetName(definitionsListNode), "ol"))
		{
			TidyNode definitionNode = tidyGetChild(definitionsListNode);

			while (definitionNode)
			{
				Definition *definition = NULL;

                if (!scrapeDefinitionFromTree(definitionsDocument, &definition, &definitionNode))
                {
                    if (definition)
                        destroyDefinition(definition);
                    
                    if (definitions)
                        destroyDefinitions(definitions);
                    
                    return NULL;
                }

                if (!definitions)
                {
                    definitions = createDefinitions(definition);
                    if (!definitions)
                    {
                        printf("Unable to allocate space for definitions\n");
                        destroyDefinition(definition);
                        return NULL;
                    }
                }
                else
                {
                    if (!pushDefinitionDefinitions(definitions, definition))
                    {
                        printf("Unable to allocate space for definitions\n");
                        destroyDefinition(definition);
                        destroyDefinitions(definitions);
                        return NULL;
                    }
                }

				definitionNode = tidyGetNext(definitionNode);
			}
		}

		definitionsListNode = tidyGetNext(definitionsListNode);
	}

    return definitions;
}

static int scrapeDefinitionFromTree(TidyDoc *definitionsDocument, Definition **definition, TidyNode *rootNode)
{
    TidyNodeType nodeType = tidyNodeGetType(*rootNode);

    if (nodeType == TidyNode_Text)
    {
        TidyBuffer definitionTextBuffer = {};
        tidyBufInit(&definitionTextBuffer);
        if (tidyNodeGetValue(*definitionsDocument, *rootNode, &definitionTextBuffer))
        {
            if (!(*definition))
            {
                *definition = createDefinition(definitionTextBuffer.bp);
                if (!definition)
                {
                    printf("Unable to allocate space for definition\n");
                    tidyBufFree(&definitionTextBuffer);
                    return 0;
                }
            }
            else
            {
                if (!appendDefinition(*definition, definitionTextBuffer.bp))
                {
                    printf("Unable to allocate space for definition\n");
                    tidyBufFree(&definitionTextBuffer);
                    return 0;
                }
            }
        }
        tidyBufFree(&definitionTextBuffer);
    }

    TidyNode childNode = tidyGetChild(*rootNode);
    while (childNode)
    {
        if (!scrapeDefinitionFromTree(definitionsDocument, definition, &childNode))
            return 0;
        
        childNode = tidyGetNext(childNode);
    }

    return 1;
}

static int wordsChunkSelector(TidyNode *nodeToSelect)
{
	TidyAttr classAttribute = tidyAttrGetById(*nodeToSelect, TidyAttr_CLASS);
	const char *classValue = tidyAttrValue(classAttribute);

	if (!classValue)
		return 0;

	return !strcmp("mw-allpages-chunk", classValue);
}

static int navigationSelector(TidyNode *nodeToSelect)
{
	TidyAttr classAttribute = tidyAttrGetById(*nodeToSelect, TidyAttr_CLASS);
	const char *classValue = tidyAttrValue(classAttribute);

	if (!classValue)
		return 0;

	return !strcmp("mw-allpages-nav", classValue);
}

static int definitionsOutputSelector(TidyNode *nodeToSelect)
{
	TidyAttr classAttribute = tidyAttrGetById(*nodeToSelect, TidyAttr_CLASS);
	const char *classValue = tidyAttrValue(classAttribute);

	if (!classValue)
		return 0;

	return !strcmp("mw-parser-output", classValue);
}
