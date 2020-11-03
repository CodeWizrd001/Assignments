#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int check(char *pwd) 
{
    if(strlen(pwd)==10)
        return 0 ;
    printf("Enter Password Of Length 10\n") ;
}

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

    do {
        printf("Enter Password : \n") ;
        scanf("%s",pwd) ;
    } while(check(pwd)) ;
    *p1_flag = 1 ;

    while(*p3_flag == -1)
    {
        sleep(1) ;
    }

    if(*strength == 1)
        printf("Password Is Strong\n") ;
    else if(*strength == 0)
        printf("Password Is Weak\n") ;
    else 
        printf("Password Strength Is Not Set\n") ; 

    shmdt(pwd); 
    return 0; 
} 