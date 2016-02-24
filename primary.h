#pragma once

#define MAXSIZE     128

void* Primary();
void die(char *s);

struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
};