#ifndef POST_H
#define POST_H
struct memory {
	char *response;
  	size_t size;
};

// Can hold up to 1000 nouns and adjectives
struct words {
	char* noun[1000];
	char* adjective[1000];
};
 
size_t cb(void *data, size_t size, size_t nmemb, void *clientp);

void postdiscord(int argc, char* argv[]);

#endif

#define MESSAGE_SIZE 2000
