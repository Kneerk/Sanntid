#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "primary.h"


void die(char *s)
{
  perror(s);
  exit(1);
};
int i = 0;
int msqid;
int msgflg = IPC_CREAT | 0666;
key_t key;
struct msgbuf sbuf;
struct msgbuf rcvbuffer;
size_t buflen;
double timeWaited = 0;
struct msqid_ds *buf;
struct msqid_ds messageqid;


void* Primary(){
    buf = &messageqid;
    key = 1234;
    //printf("%s", "vi er her \n");
    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      die("msgget");
    //Message Type
    sbuf.mtype = 1;
    sleep(1);
    buflen = strlen(sbuf.mtext) + 1 ;
    int a = 1;
    while(a){
      //  printf("%s", "vi i while \n");

        if ((msqid = msgget(key, 0666)) < 0){
            die("msgget");
        }

        
        //Receive an answer of message type 1.
        if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 0, IPC_NOWAIT) < 0){
          //  printf("%s", "vi inni while \n");
            timeWaited = difftime(time(0), buf->msg_stime);
         //   printf("%f", timeWaited);
            if(timeWaited > 3){
                a = 0;             
            }
        }
    }
    
    //Create backup
    if(rcvbuffer.mtext != NULL){
        i = atoi(rcvbuffer.mtext);
        i++;
    }

    pthread_t t1;
    pthread_create(&t1, NULL, Primary, NULL);
    
    //Send messages
    while(1){
        sprintf(sbuf.mtext, "%d", i);

        if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0){
            //printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
            die("msgsnd");
        }

        else{
            printf("%i\n", i);
        }
       // printf("%s", "hoho vi kom forbi");
        msgctl(msqid, IPC_STAT, buf);
        i++;
        if(i == 4 || i == 7){
            pthread_exit(Primary);
        }
        sleep(1);
    }
    exit(0);
}

