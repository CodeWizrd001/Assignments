#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <ctype.h>
  
int main() 
{
    key_t key = ftok("shmfile",65); 

    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    
    void *base ;
    base = (char*) shmat(shmid,(void*)0,0); 

    char *pwd = base ;
    int *p1_flag = base + 20 ;
    int *p2_flag = p1_flag + 1 ;
    int *p3_flag = p2_flag + 1 ;
    int *alnum = p3_flag + 1 ;
    int *special = alnum + 1 ;
    int *strength = special + 1 ;

    *p1_flag = -1 ;
    *p2_flag = -1 ;
    *p3_flag = -1 ;
    *alnum = 0 ;
    *special = 0 ;
    *strength = -1 ;
    
    do
    {
        sleep(1) ;
    } while(*p1_flag==-1) ;

    for(int i=0;i<10;i+=1)
    {
        if(isalnum(pwd[i]))
            *alnum += 1 ;
        else 
            *special += 1 ;
    }
    
    *p2_flag = 1 ;

    shmdt(base) ; 
    shmctl(shmid,IPC_RMID,NULL) ;
}