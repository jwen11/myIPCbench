#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include "../include/message.h"


#define LOG

int comp (const void* a ,const void* b){
	return *(double*)a - *(double*)b;
}


int main(int argc, char** argv)
{
    struct my_msgbuf bufA, bufB;
    int msgidA, msgidB;
    key_t keyA, keyB;
	
	int i;	

	char buff[100];
	char tmp[100];
	time_t now;
	double latency [ITER];
	double latency_sort [ITER];
	double maxLat, sum, avgLat;
	struct timeval tstart, tend;
	FILE *fp;


#ifdef LOG	
	buff[0] ='\0';
	strcat(buff,"./log/");
	
	now = time(0);
	strftime(tmp,100,"%Y-%m-%d_%H%M%S",localtime(&now));
	strcat(buff, tmp);
	strcat(buff,".log");
	printf("%s\n",buff);
	fp = fopen (buff, "w");	
#endif
    if ((keyA = ftok(MYPATH, 'A')) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msgidA = msgget(keyA, 0644 | IPC_CREAT)) == -1) {
        perror("msgget keyA");
        exit(1);
    }

    if ((keyB = ftok(MYPATH, 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msgidB = msgget(keyB, 0644 | IPC_CREAT)) == -1) {
        perror("msgget keyB");
        exit(1);
    }
    

    bufB.mtype = 1; /* we don't really care in this case */
	memset(bufB.mtext, '0', MSGSIZE-1);
	bufB.mtext[MSGSIZE-1] = '\0';
	
	maxLat = sum = avgLat = 0.0;
	for (i = 0; i <ITER; ++i) {

		gettimeofday (&tstart, NULL);
        if (msgsnd(msgidB, &bufB, MSGSIZE, 0) == -1) 
            perror("msgsnd");

		if (msgrcv(msgidA, &bufA, sizeof bufA.mtext, 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        
		gettimeofday (&tend, NULL);

		latency[i] =  ((double)tend.tv_sec * 1.0e6 + tend.tv_usec) -((double)tstart.tv_sec * 1.0e6 +tstart.tv_usec);
		latency_sort[i] = latency[i]; 
		if (latency[i] > maxLat) maxLat = latency[i];
		sum += latency[i];

    }
		avgLat = sum/ITER;

		qsort(latency_sort, ITER, sizeof(double), comp);

	printf("Overall %d iterations:\n", ITER);
	printf("The    max latency is %d\n", (int)maxLat);
	printf("The    avgLat latency is %d\n", (int)avgLat);
	printf("The median latency is %d\n", (int)(latency_sort[ITER/2]));
		
#ifdef LOG	
	fprintf(fp,"Overall %d iterations:\n", ITER);
	fprintf(fp,"The    max latency is %d\n", (int)maxLat);
	fprintf(fp,"The    avgLat latency is %d\n", (int)avgLat);
	fprintf(fp,"The median latency is %d\n", (int)(latency_sort[ITER/2]));
	for (i = 0; i <ITER; ++i) {
		fprintf(fp,"%5d:    %10d\n",i,(int)latency[i]);
	}

#endif
    return 0;
}
