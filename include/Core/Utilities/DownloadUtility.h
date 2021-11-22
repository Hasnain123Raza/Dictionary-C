#ifndef DOWNLOAD_UTILITY_H
#define DOWNLOAD_UTILITY_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <tidy/tidybuffio.h>

#define DISABLE_CURLOPT_SSL_VERIFYPEER

int downloadHTML(char *url, TidyBuffer *downloadBuffer);

#endif