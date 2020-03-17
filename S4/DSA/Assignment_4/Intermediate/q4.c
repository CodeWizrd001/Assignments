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
	struct Node *lC ;
	struct Node *sib ;
} Node ; 

void print(Node*) ;
Node *Union(Node*,Node*) ;

Node *Link(Node *x,Node *y)
{
	x->sib = y->lC ;
	y->lC = x ;
	x->par = y ;
	y->degree += 1 ;
	return y ;
}

Node *min(Node *H)
{
	if(H==NULL)
		return NULL ;
	Node *m = H ;
	while(H!=NULL)
	{
		if(H->data<m->data)
			m = H ;
		H = H->sib ;
	}
	return m ;
}

Node *reverse(Node *x)
{
	Node *temp = x ;
	Node **arr = (Node **) calloc(1000,sizeof(Node*)) ;
	int i = 0 ;
	if(x==NULL)
		return NULL ; 
	while(temp!=NULL)
	{
		arr[i++] = temp ;
		temp->par = NULL ;
		temp = temp->sib ;
	}
	int j = i-1 ; 
	i -= 1 ;
	while(i>0)
	{
		arr[i]->par = NULL ;
		arr[i]->sib = arr[i-1] ;
		i -= 1 ;
	}
	arr[0]->sib = NULL ;
	temp = arr[j] ;
	free(arr) ;
	return temp ;
}

Node *extractMin(Node *H,int p)
{
	if(p) 
		if(H==NULL)
			fprintf(Fout,"-1\n") ;
	Node *m = min(H) ;
	m->par = NULL ;
	m->sib = NULL ;
	if(p) 
		fprintf(Fout,"%d\n",m->data) ;
	m->data = INT_MIN ;
	if(m==H)
		H = H->sib ;
	else 
		for(Node *tmp = H ; tmp!=NULL ; tmp = tmp->sib)
		{
			if(tmp->sib == m)
			{
				tmp->sib = m->sib ;
				break ;
			}
		}
	Node *x,*y ;
	x = m->lC ;
	x = reverse(x) ;
	H = Union(H,x) ;
	return H ;
}

Node *merge(Node *p,Node *q)
{
	if(p==NULL)
		return q ;
	else if(q==NULL)
		return p ;
	else if(p->degree <= q->degree)
	{
		p->sib = merge(p->sib,q) ;
		return p ;
	}
	else 
	{
		q->sib = merge(p,q->sib) ;
		return q ;
	}
}

Node *consolidate(Node *h)
{
	Node *z ; 
	if(h==NULL)
		return NULL ;
	else 
	{	
		if(h->sib==NULL)
			return h ;
		else 
		{
			if(h->sib->degree > h->degree)
			{
				h->sib = consolidate(h->sib) ;
				return h ;
			}
			else 
			{
				if((h->sib->sib==NULL)||(h->sib->sib->degree > h->degree))
				{
					z = h->sib->sib ;
					if(h->data < h->sib->data)
					{
						h = Link(h->sib,h) ;
						h->sib = z ;
						h = consolidate(h) ;
					}
					else 
					{
						h = Link(h,h->sib) ;
						h->sib = z ; 
						h = consolidate(h) ;
					}
				}
				else 
					h->sib = consolidate(h) ;
				return h ;
			}
		}
	}
}

Node *insert(Node *H,Node *x)
{
	if(H==NULL)
		return x ;
	else if(H->degree > x->degree)
	{
		x->sib = H  ;
		return x ;
	}
	else if(H->degree == x->degree)
	{
		H = Union(H,x) ;
		return H ;
	}
}

Node *Union(Node *h,Node *g)
{
	if(h==NULL)
		return g ;
	if(g==NULL)
		return h ;
	Node *H = NULL ;
	H = merge(h,g) ;
	H = consolidate(H) ;
	return H ;
}

// Function To Print Root List 
void print(Node *h)
{
	while(h!=NULL)
	{
		printf("(%#x %d) ",h ,h->data ) ;
		h = h->sib ;
	}
	printf("\n") ;
}


Node *nodeOf(Node *A,int n,int k)
{
	Node *temp = NULL ;
	for(int i=0;i<n;i+=1)
	{
		if(A[i].data == k)
		{
			temp = &(A[i]) ;
			break ;
		}
	}
	return temp ; 
}

int cIndex(Node *A,int k,int n)
{
	for(int i=0;i<n;i+=1)
		if(A[i].data == k )
			return i ;
	return -1 ;
}

int dIndex(Node **A,Node *x,int n)
{
	for(int i=0;i<n;i+=1)
	{
		if(A[i]==x)
			return i ;
	}
	return -1 ;
}

Node *Decrease(Node *A,int n,Node *x,int k)
{
	x->data -= k ;
	int a = x->data ;
	Node *B = (Node *) calloc(n,sizeof(Node)) ;
	for(int i=0;i<n;i+=1)
		B[i] = A[i] ;
	Node *X = x ;
	int t ;
	while(X!=NULL&&((X->par)!=NULL))
	{
		if(X->par->data > X->data) 
		{
			t = X->par->data ;
			X->par->data = X->data ;
			X->data = t ;
		}
		X = X->par ;
	}
	int b = x->data ;
	int c , d ;
	c = cIndex(B,a,n) ;
	d = cIndex(B,b,n) ;
	B[c].data = b ;
	B[d].data = a ;
	for(int i=0;i<n;i+=1)
		A[i].data = B[i].data ;
	return 0 ;
}

void main()
{
	int n ;
	int i,j,k ;
	int min_ = INT_MAX ;
	Fout = stdout ;
	Fin = stdin ;
	char ch[5] ;
	fscanf(Fin,"%d",&n) ;
	Node *A = (Node*) calloc(n,sizeof(Node)) ;
	Node *H = NULL ;
	Node *x = NULL ; 
	while(fscanf(Fin,"%s",ch)&&(!feof(Fin))) 
	{
		if(!strcmp("insr",ch))
		{
			fscanf(Fin,"%d %d",&j,&k) ;
			A[j].data = k ;
			A[j].degree = 0 ;
		    A[j].sib = NULL ;
			A[j].par = NULL ; 	
			H = insert(H, A+j) ; 
			if(k<min_)
				min_ = k ;
		}
		else if(!strcmp("del",ch))
		{
			fscanf(Fin,"%d",&j) ;
			x = A+j ;
			fprintf(Fout,"%d\n",x->data) ;
			Decrease(A,n,x,INT_MIN) ;
			H = extractMin(H,0) ;
		}
		else if(!strcmp("decr",ch)) 
		{
			fscanf(Fin,"%d %d",&j,&k) ;
			x = A+j ;
			Decrease(A,n,x,k) ;
		}
		else if(!strcmp("extr",ch))
			H = extractMin(H,1) ;
		else if(!strcmp("prin",ch))
			print(H) ;
		else if(!strcmp("min",ch))
			fprintf(Fout,"%d\n",min(H)->data) ;
		else if(!strcmp("tc",ch))
		{
			int x = 0 ;
			Node *t = H ;
			while(t!=NULL)
			{
				x += 1 ;
				t = t->sib ;
			}
			fprintf(Fout,"%d\n",x) ;
		}
		else if(!strcmp("stop",ch))
			exit(0) ;
	}
}

