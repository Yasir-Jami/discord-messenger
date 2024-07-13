#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h> /* for realloc */
#include <string.h> /* for memcpy */
#include "post.h"
 
size_t cb(void *data, size_t size, size_t nmemb, void *clientp)
{
	size_t realsize = size * nmemb;
      	struct memory *mem = (struct memory *)clientp;
 
	char *ptr = realloc(mem->response, mem->size + realsize + 1);
  	if(!ptr)
		return 0;  /* out of memory! */
 
	mem->response = ptr;
  	memcpy(&(mem->response[mem->size]), data, realsize);
	mem->size += realsize;
	mem->response[mem->size] = 0;
 
	return realsize;
}

void postdiscord(int argc, char* argv[]){
	int messageSize = MESSAGE_SIZE; // Discord character limit
	char* servername = "super noobs"; // get server name from webhook url 
	char message[messageSize];
	char jsonObj[messageSize+30];
	char* url;
	
	// Get user input if no arguments
	if (argv[1]){
		if (strcmp(argv[1], "in") == 0){
			// User message
			printf("Enter message: ");
			fgets(message, messageSize, stdin);
			// Chomp newline
			size_t ln = strlen(message) - 1;
			if (message[ln] == '\n')
				message[ln] = '\0';
		}	
	
		else {
			strcpy(message, argv[1]);
			for (int i = 2; i < argc; i++){
				strcat(message, " ");
				strcat(message, argv[i]);
			}
		}
	}
	else {
		exit(EXIT_SUCCESS);
	}

	sprintf(jsonObj, "{\"content\": \"%s\"}", message);
	printf("\nSending message:\n\"%s\"\nto %s...\n\n", message, servername);

	// Headers
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type:application/json");

	// curl variables
	CURL *curl = curl_easy_init();
	CURLcode res;
	struct memory chunk = {0};

	// Build and send request
	if (curl){
		// Create request
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	    	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
    		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb); // WriteMemoryCallBack
	    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    		//curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
		
		// Perform curl
	   	res = curl_easy_perform(curl);
		// Free buffer
		free(chunk.response);

		curl_easy_cleanup(curl);
		printf("curl code %d\n", res);
	}
	curl_global_cleanup();	
}
