#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

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
    float avg = 0 , stdev = 0 ;
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
    
    read(fd[2],L,5 * sizeof(L[0]));
    read(fd[2],&avg,sizeof(avg)) ;
    read(fd[2],&stdev,sizeof(stdev)) ;
    for(int i=0;i<5;i+=1) 
    {
        if(L[i]==avg)
            category[i] = 0 ;
        else if(L[i] > avg + stdev)
            category[i] = 1 ;
        else if(L[i] < avg - stdev)
            category[i] = 4 ;
        else if(L[i] > avg && L[i] <= avg + stdev)
            category[i] = 2 ;
        else if(L[i] < avg && L[i] >= avg - stdev)
            category[i] = 3 ;
    }
    write(fd[0],category,5*sizeof(category[0])) ;

    close(fd[0]) ;
    close(fd[1]) ;
    close(fd[2]) ;
}