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
    
    printf("Enter The 5 Values :\n") ;
    do {
        scanf("%f%f%f%f%f",L,L+1,L+2,L+3,L+4) ;
     } while (check(L)) ;
    write(fd[1],L,5 * sizeof(L[0])) ;
    read(fd[0],category,5 * sizeof(category[0])) ;
    for(int i=0;i<5;i+=1) 
    {
        switch(category[i])
        {
            case 0 :break ;
            case 1 :L[i] -= 3 ;
                    break ;
            case 2 :L[i] -= 1.5 ;
                    break ;
            case 3 :L[i] += 2 ;
                    break ;
            case 4 :L[i] += 2.5 ;
                    break ;
            default:break ;
        }
    }
    printf("Revised Temperatures\n") ;
    printf("L1 : %7.2f L2 : %7.2f L3 : %7.2f L4 : %7.2f L5 : %7.2f\n",L[0],L[1],L[2],L[3],L[4]) ;

    close(fd[0]) ;
    close(fd[1]) ;
    close(fd[2]) ;
}