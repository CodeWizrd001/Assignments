#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

int isParent(int *pids) 
{
    return (pids[0]&&pids[1]&&pids[2]) ;
}

char *itoa(int x) 
{
    char* ans = (char *) calloc(10,sizeof(char)) ;
    sprintf(ans, "%d", x);
    return ans ;
}

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

int main()
{
    int pipefds[3][2] ;
    int returnstatus ;
    int pids[3] = {0,0,0} ;
    int childId = 0 ;
    int code = 0 ; 
    int childReturn[3] ;
    char writemessage[20] ;
    char readmessage[20];
    float L[5] = {0,0,0,0,0} ;
    int category[5] = {0,0,0,0,0} ;
    returnstatus = pipe(pipefds[0]);
    returnstatus = pipe(pipefds[1]);
    returnstatus = pipe(pipefds[2]);
    if (returnstatus == -1) 
    {
        printf("Unable to create pipe\n");
        return 1;
    }
    pids[0] = fork();
    if(pids[0] != 0) 
    {
        pids[1] = fork() ; 
        if(pids[1] != 0) 
        {
            pids[2] = fork() ; 
            if (pids[2] == 0)
            {
                childId = 3 ;
            }
        }
        else
        {
            childId = 2 ;
        }
    }
    else 
    {
        childId = 1 ;
    }
    
    // Parent process
    if (isParent(pids)) 
    {
        int read_ = 0 ;
        float value ;
        waitpid(pids[0],childReturn,0) ;
        waitpid(pids[1],childReturn + 1,0) ;
        waitpid(pids[2],childReturn + 2,0) ;
    } 
    else 
    {
        //Child process
        int read_ ;
        float avg ;
        float stdev ; 
        switch(childId)
        {
            case 1 :printf("Enter The 5 Values :\n") ;
                    do {
                        scanf("%f%f%f%f%f",L,L+1,L+2,L+3,L+4) ;
                    } while (check(L)) ;
                    int tCategory[5] = {0,0,0,0,0} ;
                    write(pipefds[1][1],L,5 * sizeof(L[0])) ;
                    read(pipefds[childId-1][0],tCategory,5 * sizeof(tCategory[0])) ;
                    for(int i=0;i<5;i+=1) 
                    {
                        switch(tCategory[i])
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
                    break ;
            case 2 :read(pipefds[childId - 1][0],L,5 * sizeof(L[0]));
                    write(pipefds[2][1],L,5 * sizeof(L[0])) ;
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
                    write(pipefds[2][1],&avg,sizeof(avg)) ;
                    write(pipefds[2][1],&stdev,sizeof(stdev)) ;
                    break ;
            case 3 :read(pipefds[childId-1][0],L,5 * sizeof(L[0]));
                    read(pipefds[childId-1][0],&avg,sizeof(avg)) ;
                    read(pipefds[childId-1][0],&stdev,sizeof(stdev)) ;
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
                    write(pipefds[0][1],category,5*sizeof(category[0])) ;
                    break ;
            default:break ;
        }
    }
    return 0;
}