#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <math.h>

int check(float *L)
{
    for(int i=0;i<5;i+=1)
    {
        if(L[i] < 15 || L[i] > 45)
        {
            printf("One of the Values Not In Range 15 to 45\n") ;
            printf("Re-enter values \n") ;
            return 1 ;
        }
    }
    return 0 ;
}

void main()
{
    float avg = 0 ,stdev = 0 ;
    float L[5] = {0,0,0,0,0} ;
    int category[5] = {0,0,0,0,0} ;

    int fd[3] ;

    char * fifo[3] = {"/tmp/fifo1","/tmp/fifo2","/tmp/fifo3"}; 

    mkfifo(fifo[0], 0666); 
    mkfifo(fifo[1], 0666); 
    mkfifo(fifo[2], 0666); 
        
    fd[0] = open(fifo[0], O_RDWR); 
    fd[1] = open(fifo[1], O_RDWR); 
    fd[2] = open(fifo[2], O_RDWR); 
    
    read(fd[1],L,5 * sizeof(L[0]));
    write(fd[2],L,5 * sizeof(L[0])) ;
    avg = 0 ;
    for(int i=0;i<5;i+=1) 
    {
        avg += L[i] ;
    }
    avg /= 5 ;
    stdev = 0 ;
    for(int i=0;i<5;i+=1) 
    {
        stdev += pow(L[i]-avg,2) ;
    }
    stdev /= 5 ;
    stdev = sqrt(stdev) ;
    write(fd[2],&avg,sizeof(avg)) ;
    write(fd[2],&stdev,sizeof(stdev)) ;

    close(fd[0]) ;
    close(fd[1]) ;
    close(fd[2]) ;
}