#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include "../include/message.h"


int main(void)
{
    struct my_msgbuf bufA, bufB;
    int msgidA, msgidB;
    key_t keyA, keyB;
	
	int i;	

	struct timespec tstart, tend;	

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
    

    bufA.mtype = 1; /* we don't really care in this case */
	memset(bufA.mtext, '0', MSGSIZE-1);
	bufA.mtext[MSGSIZE-1] = '\0';

	
	clock_getres (CLOCK_MONOTONIC, &tstart);
	printf("The clock resolution is %ld second, %ld nano second\n", tstart.tv_sec, tstart.tv_nsec);

	clock_gettime (CLOCK_MONOTONIC, &tstart);
	for (i = 0; i <ITER; ++i) {

		if (msgrcv(msgidB, &bufB, sizeof bufB.mtext, 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        if (msgsnd(msgidA, &bufA, MSGSIZE, 0) == -1) 
            perror("msgsnd");
        
    }
	clock_gettime(CLOCK_MONOTONIC, &tend);
	
	printf("The communication took about %.9f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
		

    if (msgctl(msgidA, IPC_RMID, NULL) == -1) {
        perror("msgctl A");
        exit(1);
    }
    if (msgctl(msgidB, IPC_RMID, NULL) == -1) {
        perror("msgctl B");
        exit(1);
    }

    return 0;
}
