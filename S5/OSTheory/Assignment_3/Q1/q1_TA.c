#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h>

struct buffer
{
    long mtype ;
    char data[200] ;
} message ;

char getGrade(float mark ,float avg)
{
        if(mark <= 19) 
            return 'E' ;
        else if(mark < 29)
            return 'B' ;
        else if(mark < 39) 
            return 'A' ; 
        else 
            return 'S' ;
}

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
        msgrcv(msgid, &message, sizeof(message.data), 10, 0); 
        printf("Mark of Student %d is : %s \n",i,message.data); 
        sscanf(message.data,"%f",marks + i-1) ;
        avg += marks[i-1] ;
    }
    avg /= 5 ;

    message.mtype = 100; 
    sprintf(message.data,"%f",avg) ;
    msgsnd(msgid, &message, sizeof(message.data), 0); 
    printf("Average Sent\n") ;

    for(int i=1;i<=5;i+=1) 
    {
        message.mtype = 100;    
        sprintf(message.data,"%c",getGrade(marks[i-1],avg)) ;
        msgsnd(msgid, &message, sizeof(message.data), 0); 
    }
    printf("Grades Sent\n") ;

    for(int i=1;i<=5;i+=1) 
    {
        message.mtype = i; 
        sprintf(message.data,"%f",marks[i-1]) ;
        msgsnd(msgid, &message, sizeof(message.data), 0); 
    }
    sleep(1) ;
    msgctl(msgid, IPC_RMID, NULL); 
}