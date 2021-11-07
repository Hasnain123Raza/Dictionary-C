#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "DownloadUtility.h"
#include "ParseUtility.h"
#include "WordsArray.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <tidy/tidy.h>
#include <tidy/tidybuffio.h>

#define BASE_URL "https://simple.wiktionary.org"
#define FIRST_PAGE_URL "/wiki/Special:AllPages?from=A"

WordsArray *downloadWords(int skip);

#endif