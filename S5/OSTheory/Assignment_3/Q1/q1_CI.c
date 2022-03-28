#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h>

struct buffer
{
    long mtype ;
    char data[200] ;
} message ;


void main()
{

    key_t key; 
    int msgid; 

    key = ftok("progfile", 65); 
    msgid = msgget(key, 0666 | IPC_CREAT); 

    int i ;

    float avg ;
    float marks[5] = {
        10,
        20,
        30,
        40,
        50
    } ;

    for(int i=1;i<=5;i+=1) 
    {
        message.mtype = 10; 
        sprintf(message.data,"%f",marks[i-1]) ;
        // printf("Write Data : %d\n",msgid); 
        msgsnd(msgid, &message, sizeof(message.data), 0);
    }

    msgrcv(msgid, &message, sizeof(message.data), 100, 0); 
    printf("Average is : %s \n",message.data); 

    sscanf(message.data,"%f",&avg) ;

    for(i=1;i<=5;i+=1) 
    {
        msgrcv(msgid, &message, sizeof(message.data), 100, 0); 
        printf("Grade of Student %d is : %s \n",i,message.data);
    }
}