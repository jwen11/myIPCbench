#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CACHE_SIZE (8 *1024 *1024)
#define NUM	(40)
int main(int argc, char** argv)
{
	int* dummy;
	int i;
	int dst, src;
	int ramsize = NUM*CACHE_SIZE;
	dummy = malloc (ramsize *sizeof (int) );
	for ( i =0 ; i <ramsize; ++i){
		dummy[i] = i;
	}
	while (1){
		dst = rand() % ramsize;
		src = rand() % ramsize;
		dummy[src] = dummy[dst];
	}
	free (dummy);

    return 0;
}
