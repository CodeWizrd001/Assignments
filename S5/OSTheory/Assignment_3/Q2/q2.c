#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void matPrint(int *x,int r,int c) 
{
    for(int i=0;i<r;i+=1) 
    {
        for(int j=0;j<c;j+=1)
            printf("%d ",*(x + i*c + j)) ;
        printf("\n") ;
    }
}

int* copy(int *x,int r,int c)
{
    int *temp = (int *) calloc(r*c,sizeof(int)) ;
    for(int i=0;i<r;i+=1) 
        for(int j=0;j<c;j+=1)
            *(temp + i*c + j) = *(x + i*c + j) ;
    return temp ;
}

int* getSafeState(int *rem,int *alloc,int *avail,int nProc, int nRes)
{
    int *safeSeq = (int *) calloc(nProc,sizeof(int)) ;

    // Making Copies to use
    int *r = copy(rem,nProc,nRes) ;
    int *a = copy(alloc,nProc,nRes) ;
    int *av = copy(avail,1,nRes) ;

    int safeProc , i , j , k , safe;
    for(k=0;k<nProc;k+=1)
    {
        safeProc = -1 ;
        for(i=0;i<nProc;i+=1)
        {
            safe = 1 ; 
            for(j=0;j<nRes;j+=1) 
            {
                if(*(r + i*nRes +j) > av[j])
                {
                    safe = 0 ;
                    break ;
                }
            }
            if(safe == 1) 
            {
                safeProc = i ;
                break ;
            }
        }
        if(safeProc != -1) 
        {
            safeSeq[k] = safeProc + 1 ;
            for(j=0;j<nRes;j+=1) 
            {
                av[j] += *(a + safeProc * nRes + j) + *(r + safeProc * nRes + j) ;
                *(r + safeProc * nRes + j) = INT_MAX ;
                *(a + safeProc * nRes + j) = -1 ;
            }
        }
        else
        {
            for(int p=0;p<nProc;p+=1)
                safeSeq[i] = -1 ;
        }
        
    }
    free(a) ;
    free(r) ;
    free(av) ;
    return safeSeq ;
}

int checkSafe(int *seq,int *rem,int *alloc,int *avail,int nProc,int nRes)
{
    int *r = copy(rem,nProc,nRes) ;
    int *a = copy(alloc,nProc,nRes) ;
    int *av = copy(avail,1,nRes) ;

    int safe , i , j , k ;

    for(i=0;i<nProc;i+=1)
    {
        k = seq[i] ;
        for(j=0;j<nRes;j+=1)
        {
            if(*(r + k*nRes +j) > av[j])
            {
                free(a) ;
                free(r) ;
                free(av) ;
                return 0 ;
            }
        }
        for(j=0;j<nRes;j+=1) 
        {
            av[j] += *(a + k * nRes + j) + *(r + k * nRes + j) ;
            *(r + k * nRes + j) = INT_MAX ;
            *(a + k * nRes + j) = -1 ;
        }
    }

    free(a) ;
    free(r) ;
    free(av) ;
    return 1 ;
}

void main()
{
    FILE *f ;

    int nProc , nRes , i , j , flag;

    f = stdin ;
    printf("Enter Number of Processes : ") ;
    fscanf(f,"%d",&nProc) ;
    printf("\nEnter Number of Resources : ") ;
    fscanf(f,"%d",&nRes) ;

    int *allocTable = (int *) calloc(nProc * nRes ,sizeof(int)) ;
    int *maxTable = (int *) calloc(nProc * nRes ,sizeof(int)) ;
    int *remTable = (int *) calloc(nProc * nRes ,sizeof(int)) ;
    int *avail = (int *) calloc(nRes,sizeof(int)) ;
    int *cSec = (int *) calloc(nProc,sizeof(int)) ;
    int *rSeq = (int *) calloc(nRes,sizeof(int)) ; 
    int *res ;

    // Read Available Resources
    printf("\nEnter Available Resources : ") ;
    for(i=0;i<nRes;i+=1)
        fscanf(f,"%d",avail + i) ;
    
    // Read AllocTable
    printf("\nEnter AllocTable : ") ;
    for(i=0;i<nProc;i+=1) 
        for(j=0;j<nRes;j+=1)
            fscanf(f,"%d",allocTable + i*nRes + j) ;

    // Read MaxTable
    printf("\nEnter MaxTable : ") ;
    for(i=0;i<nProc;i+=1) 
        for(j=0;j<nRes;j+=1)
            fscanf(f,"%d",maxTable + i*nRes + j) ;

    // Calculate Remtable
    for(i=0;i<nProc;i+=1) 
        for(j=0;j<nRes;j+=1)
            *(remTable + i*nRes + j) = *(maxTable + i*nRes + j) - *(allocTable + i*nRes + j) ;

    // Calculate Remaining Resources
    for(i=0;i<nProc;i+=1) 
        for(j=0;j<nRes;j+=1)
            avail[j] -= *(allocTable + i*nRes + j) ;

    printf("\n\n") ;
    printf("Available Resources \n") ;
    matPrint(avail,1,nRes) ;
    printf("\n") ;
    printf("Max Table \n") ;
    matPrint(maxTable,nProc,nRes) ;
    printf("\n") ;
    printf("Alloc Table \n") ;
    matPrint(allocTable,nProc,nRes) ;
    printf("\n") ;
    printf("Required \n") ;
    matPrint(remTable,nProc,nRes) ;
    printf("\n") ;

    char ch = 'y' ;
    while(ch != 't' || ch == 'T') 
    {
        fscanf(f,"%c",&ch) ;
        switch(ch)
        {
            case 'a' :  res = getSafeState(remTable,allocTable,avail,nProc,nRes) ;
                        printf("Safe Sequence\n") ;
                        for(i=0;i<nProc;i+=1)
                            printf("%d ",res[i]) ;
                        printf("\n") ;
                        break;
            case 'b' :  printf("Enter Sequence : \n") ;
                        for(i=0;i<nProc;i+=1)
                        {
                            fscanf(f,"%d",cSec + i) ;
                            cSec[i] -= 1 ;
                        }
                        if(checkSafe(cSec,remTable,allocTable,avail,nProc,nRes))
                            printf("SAFE\n") ;
                        else
                            printf("NOT SAFE\n") ;
                    
                        break;
            case 'c' :  printf("Enter Request : \n") ;
                        for(i=0;i<nRes;i+=1)
                        {
                            fscanf(f,"%d",rSeq + i) ;
                        }
                        flag = 1 ;
                        for(j=0;j<nRes;j+=1) 
                        {
                            if(avail[j] < rSeq[j])
                            {
                                flag = 0 ;
                                break ;
                            }
                        }
                        if(flag == 1)
                            printf("CAN BE ALLOCATED\n") ; 
                        else 
                            printf("CANNOT BE ALLOCATED\n") ;
                        break;
            default :   break;
        }
    }
}