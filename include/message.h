#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define MSGSIZE (128)
#define ITER	(1024*2*100)
#define MYPATH	"./Makefile"

struct my_msgbuf {
    long mtype;
    char mtext[MSGSIZE];
};
#endif
