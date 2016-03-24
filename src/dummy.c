#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CACHE_SIZE (8 *1024 *1024)
#define NUM	(10)
int main(int argc, char** argv)
{
	char* dummy;
	int i;
	while (1){
		dummy = malloc (CACHE_SIZE *NUM);
		memset (dummy, 0, CACHE_SIZE*NUM);
		for ( i =0 ; i < NUM * CACHE_SIZE; ++i){
			dummy[i] = (char)i;
		}
		free (dummy);
	}

    return 0;
}
