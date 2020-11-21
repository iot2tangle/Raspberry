#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <curl/curl.h>
#include "http.h"

CURL *handle;
int isEndpoint;

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

bool get_json(char* j, const char* endp, int p, const char* _top, const char* _us, const char* _pass, long t)
{
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if(handle) 
    {
        struct string s;
    	init_string(&s);
        curl_easy_setopt(handle, CURLOPT_URL, endp);
        curl_easy_setopt(handle, CURLOPT_PORT, p);
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, t-3);	/* timeout is: 'Time set by user  minus  3', this is for give the user until the last seconds the opportunity to see if their message was sent to the tangle (when the tangle is congested) */
        curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);
    	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writefunc);
    	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &s);
        isEndpoint = curl_easy_perform(handle);
	
		strcpy(j, s.ptr);
    	free(s.ptr);
		
        curl_easy_cleanup (handle);
    }
    curl_global_cleanup();
    
    // Endpoint response
    printf("\n");
    if (isEndpoint == 0)	
		return true; 
    else
    {
		if (isEndpoint==28)
		{
	        printf("Timeout!\n");
	        return false;
		}
		else
		{
	        printf("Failed to send Data to Endpoint!\n");
	        return false;
		}
    }
}

bool init_socket(const char* endp, int p, const char* _us, const char* _pass, bool ft_http)
{
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();
    if(handle) 
    {
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
		printf(" -- The Configuration Network is correct, getting data from The Tangle --\n");
		return true;
    }
    else
    {
		printf(" -- Endpoint is NOT detected!! -- Please, check your configuration --\n");
		return false;
    }
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}
