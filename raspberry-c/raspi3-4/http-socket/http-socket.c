#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include "http-socket.h"

#include <curl/curl.h>

CURL *handle;
int isEndpoint;

bool socket_sender(const char* endp, int p, const char* j, long t)
{
	printf("\nJSON:\n%s\n\n", j);
	printf("	Sending Data to Tangle...\n");

    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if(handle) {
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, j);
        curl_easy_setopt(handle, CURLOPT_URL, endp);
        curl_easy_setopt(handle, CURLOPT_PORT, p);
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, t-1);	/* timeout is: 'Time set by user  minus  1', this is for give the user until the last second the opportunity to see if their message was sent to the tangle (when the tangle is congested) */
        isEndpoint = curl_easy_perform(handle);

        curl_easy_cleanup (handle);
    }

    curl_global_cleanup();
	

	printf("\n			");
	if (isEndpoint == 0)
	{
		printf("*** Data Sent sucessfully To Tangle ***\n");
		return true;
	}
	else
	{
		if (isEndpoint==28)
		{
			printf("*** Timeout! The data was sent to the Tangle but no confirmation was received ***\n     If you receive this message very often you may need to increase the interval in seconds between data collection\n\n");
			return true;
		}
		else
		{
			printf("*** Failed to send Data to Endpoint! ***\n");
			return false;
		}
	}
	printf("\n\n");
}

bool isEndpointOk(const char* endp, int p)
{
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if(handle) {
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);	/* Hide the response */
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

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}
