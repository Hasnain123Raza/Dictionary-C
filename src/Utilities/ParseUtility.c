#include "ParseUtility.h"

int loadTidyDocumentFromTidyBuffer(TidyDoc *tidyDocument, TidyBuffer *inputBuffer)
{
	TidyBuffer errorBuffer = {};
	
	if (!tidyOptSetBool(*tidyDocument, TidyXhtmlOut, yes))
	{
		fprintf(stderr, "tidyOptSetBool failed with TidyXhtmlOut\n");
		return 0;
	}

	if (tidySetErrorBuffer(*tidyDocument, &errorBuffer))
	{
		fprintf(stderr, "tidySetErrorBuffer failed\n");
		return 0;
	}

	if (tidyParseBuffer(*tidyDocument, inputBuffer) == 2)
	{
		fprintf(stderr, "tidyParseBuffer failed: %s\n", errorBuffer.bp);
		tidyBufFree(&errorBuffer);
		return 0;
	}
	
	if (tidyCleanAndRepair(*tidyDocument) == 2)
	{
		fprintf(stderr, "tidyCleanAndRepair failed: %s\n", errorBuffer.bp);
		tidyBufFree(&errorBuffer);
		return 0;
	}

	if (tidyRunDiagnostics(*tidyDocument) == 2)
	{
		fprintf(stderr, "tidyRunDiagnostics failed: %s\n", errorBuffer.bp);
		tidyBufFree(&errorBuffer);
		return 0;
	}

	tidyBufFree(&errorBuffer);
	return 1;
}

int searchTidyNode(TidyNode *nodeToSearch, TidyNode *nodeFound, int(*selector)(TidyNode*))
{
	if (selector(nodeToSearch))
	{
		*nodeFound = *nodeToSearch;
		return 1;
	}
	else
	{
		TidyNode childNode = tidyGetChild(*nodeToSearch);
		while (childNode)
		{
			if (searchTidyNode(&childNode, nodeFound, selector))
				return 1;

			childNode = tidyGetNext(childNode);
		}

		return 0;
	}
}