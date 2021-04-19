#include<stdio.h>
#include<stdlib.h>
struct Node 
{
	int data;
	struct Node *l;
	struct Node *r; 
	struct Node *p;
};
typedef struct Node node;

void paren(node **t)
{
        if((*t)!=NULL)
        {
                printf("(%d  ",(*t)->data);
                paren(&(*t)->l);
                paren(&(*t)->r);
        }
        else if ((*t)==NULL)
        {
                printf("()");
                return;
        }
        printf(")");
	int tab;
}

void insert(node **t,int e)
{
        node *z=(node*)malloc(sizeof(node));
        z->data=e;
        z->l=NULL;
        z->r=NULL;
        z->p=NULL;

        node *y=NULL;
        node *x=*t;
        while((x)!=NULL)
        {
                y=x;
                if((z->data) <= (x->data))
                        x=x->l;
                else
                        x=x->r;
        }
        z->p=y;
        if(y==NULL)
        {       (*t)=z;z->l=0;}
        else if ((z->data) <= (y->data))
                y->l=z;
        else
                y->r=z;
}

void main()
{
	int n;
	scanf("%d",&n);
	node *t=NULL;
	int x;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		insert(&t,x);
	}
	paren(&t);
	printf("\n");
}

