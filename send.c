#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "post.h"

// TODO: SHOULD GET CURRENT PATH so that script runs all the time
// there's probably a pwd command in c, use that and strcat /post

// Sends message given an argc and argv
int main(int argc, char* argv[]){
	postdiscord(argc, argv);
	return 0;
}
