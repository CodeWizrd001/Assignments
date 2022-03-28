#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

FILE *Fin ;
FILE *Fout ;

typedef struct Node 
{
	int data ;
	int degree ;
	struct Node *par ;
} Node ; 

Node *newNode(int k)
{
	Node *temp = (Node*) calloc(1,sizeof(Node)) ;
	temp->degree = 0 ;
	temp->data = k ;
	temp->par = NULL ;
	return temp ;
}

Node *Find_(Node *x)
{
	while(x->par!=NULL)
		x = x->par ;
	return x ;
}

int Link(Node **A,int j,int k)
{
	
	Node *y = A[j] ;
	Node *x = A[k] ;
	x->par = y ;
	y->degree += 1 ;
}

int Linkr(Node **A,int j,int k)
{
	Node *y = A[j] ;
	Node *x = A[k] ;
	Node *a = Find_(y) ;
	Node *b = Find_(x) ;
	if(a->degree==b->degree)
	{
		b->par = a ;
		a->degree += 1 ;
	}
	else 
	if(a->degree < b->degree)
		a->par = b ;
	else
		b->par = a ;
}

void insert(Node **A,Node **B,Node **C,Node **D,int j)
{
	if(A[j]!=NULL||B[j]!=NULL||C[j]!=NULL||D[j]!=NULL)
	{
		fprintf(Fout,"PRESENT\n") ;
		return ;
	}
//	fprintf(Fout,"%d\n",j) ;
	A[j] = newNode(j) ;
	B[j] = newNode(j) ;
	C[j] = newNode(j) ;
	D[j] = newNode(j) ;
	return ;
}

Node *parent(Node *x)
{
	if(x->par==NULL)
		return x ;
	return x->par ;
}

int rep(Node *x)
{
	while((x!=NULL)&&(x->par!=NULL))
		x = x->par ;
	return x->data ;
}

int Find(Node **A,Node *x,int *S,int i)
{
//	printf("Find %d\n",i) ;
	if(x==NULL)
		return 0 ;
	Node *y = parent(x) ;
	S[i] += 1 ;
//	printf("After %d %d %d %d\n",x->data,y->data,x==y,y==x) ;
	if(x==y)
	{
//		printf("Return Find\n") ;
		return 1 ;
	}
	return Find(A,y,S,i) ;
}

int Findp(Node **A,Node *x,Node *p,int *S,int i)
{
//	printf("Find p %d \n",i) ;
	if(p==NULL) 
		return 0 ;
	Node *y = A[rep(x)] ;
	Node *z = parent(p) ;
	S[i] += 1;
//	printf("After %d %d %d %d\n",p->data,z->data,z==p,p==z) ;
	if(z==p)
	{
		if(x!=y) 
			x->par = y ;
//		printf("Return Find P\n") ;
		return 1 ;
	}
	return Findp(A,x,z,S,i) ;
}

void print(Node **A,int n)
{
	for(int i=1;i<10;i+=1)
		printf("(%d %d) ",A[i]->data,(A[i]->par)?(A[i]->par->data):0) ;
	printf("\n") ;
}

void printall(Node **A,Node **B,Node **C,Node **D,int n)
{
	print(A,n) ;
	print(B,n) ;
	print(C,n) ;
	print(D,n) ;
}

void main()
{
	int n ;
	int i,j,k ;
	int min = INT_MAX ;
	int max = INT_MIN ;
	Fout = stdout ;
	Fin = stdin ;
	char ch[5] ;
	n = 10000;
	Node **A = (Node **) calloc(n,sizeof(Node*)) ;
	Node **B = (Node **) calloc(n,sizeof(Node*)) ;
	Node **C = (Node **) calloc(n,sizeof(Node*)) ;
	Node **D = (Node **) calloc(n,sizeof(Node*)) ;

	int S[4] = {0,0,0,0} ;

	for(i=0;i<n;i+=1) 
		A[i] = B[i] = C[i] = D[i] = NULL ;

	while(fscanf(Fin,"%s",ch)&&(!feof(Fin))) 
	{
		printf("Scanned %s %d\n",ch,ch[0]=='s') ;
		if(ch[0]=='m')
		{
			fscanf(Fin,"%d",&j) ;
			insert(A,B,C,D,j) ;
			if(k<min)
				min = k ;
			if(k>max) ;
				max = k ;
		}
		else if(ch[0]=='u')
		{
			fscanf(Fin,"%d %d",&j,&k) ;
			Link(A,j,k) ;
			Linkr(B,j,k) ;
			Link(C,j,k) ;
			Linkr(D,j,k) ;
			fprintf(Fout,"%d %d %d %d \n",rep(A[k]),rep(B[k]),rep(C[k]),rep(D[k])) ;
			print(A,max) ;
			print(B,max) ;
		}
		else if(ch[0]=='f')
		{
			fscanf(Fin,"%d",&k) ;
			i = Find(A,A[k],S,0) ;
			i = Find(B,B[k],S,1) ;
//			printf("Clear 1\n");
			i = Findp(C,C[k],C[k],S,2) ;
			i = Findp(D,D[k],D[k],S,3) ;
//			printf("Clear 2\n") ;
			fprintf(Fout,"%d %d %d %d \n",rep(A[k]),rep(B[k]),rep(C[k]),rep(D[k])) ;
		}
		else if(ch[0]=='s')
			fprintf(Fout,"%d %d %d %d \n",S[0],S[1],S[2],S[3]) ;
		else 
			continue ;
	}
}

