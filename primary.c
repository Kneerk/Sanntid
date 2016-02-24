#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "primary.h"


void die(char *s)
{
  perror(s);
  exit(1);
}

int i = 0;

void* Primary(){
	int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    struct msgbuf rcvbuffer;
    struct msqid_ds messageqid;
    size_t buflen;

    printf("%s", "vi er her \n");

    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      die("msgget");

    //Message Type
    sbuf.mtype = 1;

    buflen = strlen(sbuf.mtext) + 1 ;

    int a = 1;
    while(a){
        printf("%s", "vi i while \n");

        if ((msqid = msgget(key, 0666)) < 0){
            die("msgget");
        }

        printf("%i", msqid);

        time_t timeWaited;
        //Receive an answer of message type 1.
        if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 0, msgflg) < 0){
            printf("%s", "vi inni while \n");
            timeWaited = time(0) - messageqid.msg_stime;

            if(timeWaited > 3){
                a = 0;             
            }
        }
    }
    printf("%s", "hoho vi kom forbi");
    //Create backup
    if(rcvbuffer.mtext != NULL){
        i = *rcvbuffer.mtext - '0';
    }

    pthread_t t1;
    pthread_create(&t1, NULL, Primary, NULL);

    //Send messages
    while(1){
        *sbuf.mtext = i + '0';

        if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0){
            //printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
            die("msgsnd");
        }

        else{
            printf("%i\n", i);
        }

        i++;
        sleep(1);
    }
    exit(0);
}