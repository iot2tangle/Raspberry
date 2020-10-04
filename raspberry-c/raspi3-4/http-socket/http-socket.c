#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "http-socket.h"

#include <curl/curl.h>

CURL *handle;
int isEndpoint;

bool socket_sender(const char* endp, int p, const char* j)
{
	printf("\n\nJSON:\n%s\n\n", j);

    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if(handle) {
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, j);
        curl_easy_setopt(handle, CURLOPT_URL, endp);
        curl_easy_setopt(handle, CURLOPT_PORT, p);
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, 20);
        isEndpoint = curl_easy_perform(handle);

        curl_easy_cleanup (handle);
    }

    curl_global_cleanup();

	if (isEndpoint == 0)
	{
		printf("\n\n");
		return true;
	}
	else
	{
		printf("\nFailed to send to Endpoint!\n");
		return false;
	}
}

bool isEndpointOk(const char* endp, int p)
{
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if(handle) {
        curl_easy_setopt(handle, CURLOPT_URL, endp);
        curl_easy_setopt(handle, CURLOPT_PORT, p);
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, 1);
        isEndpoint = curl_easy_perform(handle);

        curl_easy_cleanup (handle);
    }
    curl_global_cleanup();


	if (isEndpoint == 0)
	{
		printf(" -- The Configuration Network is correct, sending data to The Tangle --\n");
		return true;
	}
	else
	{
		printf(" -- Endpoint is NOT detected!! -- \n -- Please, check your configuration --\n");
		return false;
	}
}

