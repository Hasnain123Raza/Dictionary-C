#ifndef PARSE_UTILITY_H
#define PARSE_UTILITY_H

#include <stdio.h>
#include <tidy/tidy.h>
#include <tidy/tidybuffio.h>

int loadTidyDocumentFromTidyBuffer(TidyDoc *tidyDocument, TidyBuffer *inputBuffer);
int searchTidyNode(TidyNode *nodeToSearch, TidyNode *nodeFound, int(*selector)(TidyNode*));

#endif