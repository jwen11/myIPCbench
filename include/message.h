#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define MSGSIZE (1)
#define ITER	(1024*2*50)
#define MYPATH	"./Makefile"
#define SHMSZ   (1024*2*2)

struct my_msgbuf {
    long mtype;
    char mtext[MSGSIZE];
};
#endif
