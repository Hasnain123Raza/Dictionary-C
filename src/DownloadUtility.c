#include "DownloadUtility.h"

static size_t downloadWriteFunction(char *bytes, size_t size, size_t nmemb, TidyBuffer *downloadBuffer)
{
	tidyBufAppend(downloadBuffer, bytes, nmemb);
	return nmemb;
}

int downloadHTML(char *url, TidyBuffer *downloadBuffer)
{
	static int curlGlobalInitialized = 0;

	if (!curlGlobalInitialized)
	{
		if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
		{
			printf("curl_global_init failed\n");
			return 0;
		}

		atexit(curl_global_cleanup);
		curlGlobalInitialized = 1;
	}

	CURL *handle = curl_easy_init();
	if (!handle)
	{
		printf("curl_easy_init failed\n");
		return 0;
	}

	char curlErrorBuffer[CURL_ERROR_SIZE];
	if (curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, curlErrorBuffer))
	{
		printf("curl_easy_setopt failed with CURLOPT_ERRORBUFFER\n");
		curl_easy_cleanup(handle);
		return 0;
	}

	if (curl_easy_setopt(handle, CURLOPT_URL, url) != CURLE_OK)
	{
		printf("curl_easy_setopt failed with CURLOPT_URL: %s\n", curlErrorBuffer);
		curl_easy_cleanup(handle);
		return 0;
	}

	if (curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L) != CURLE_OK)
	{
		printf("curl_easy_setopt failed with CURLOPT_FOLLOWLOCATION: %s\n", curlErrorBuffer);
		curl_easy_cleanup(handle);
		return 0;
	}

#ifdef DISABLE_CURLOPT_SSL_VERIFYPEER
	if (curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L) != CURLE_OK)
	{
		printf("curl_easy_setopt failed with CURLOPT_SSL_VERIFYPEER: %s\n", curlErrorBuffer);
		curl_easy_cleanup(handle);
		return 0;
	}
#endif

	if (curl_easy_setopt(handle, CURLOPT_WRITEDATA, downloadBuffer) != CURLE_OK)
	{
		printf("curl_easy_setopt failed with CURLOPT_WRITEDATA: %s\n", curlErrorBuffer);
		curl_easy_cleanup(handle);
		return 0;
	}

	if (curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, downloadWriteFunction) != CURLE_OK)
	{
		printf("curl_easy_setopt failed with CURLOPT_WRITEFUNCTION: %s\n", curlErrorBuffer);
		curl_easy_cleanup(handle);
		return 0;
	}
	
	if (curl_easy_perform(handle) != CURLE_OK)
	{
		printf("curl_easy_perform failed: %s\n", curlErrorBuffer);
		curl_easy_cleanup(handle);
		return 0;
	}

	curl_easy_cleanup(handle);
	return 1;
}