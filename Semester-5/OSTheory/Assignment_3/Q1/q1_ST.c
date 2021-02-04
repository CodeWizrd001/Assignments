#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct buffer
{
    long mtype ;
    char data[200] ;
} message ;

void main()
{
    int i = 0 ;
    key_t key; 
    int msgid; 

    float marks[5] ;
    float avg = 0 ;

    key = ftok("progfile", 65); 
    msgid = msgget(key, 0666 | IPC_CREAT); 

    for(i=1;i<=5;i+=1) 
    {
        msgrcv(msgid, &message, sizeof(message.data), i, 0); 
        printf("Mark of Student %d is : %s \n",i,message.data); 
        sscanf(message.data,"%f",marks + i-1) ;
    }
}