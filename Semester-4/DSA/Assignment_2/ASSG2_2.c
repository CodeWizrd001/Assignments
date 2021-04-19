#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node
{
	int data;
	struct Node *l;
	struct Node *r;
	struct Node *p;
	int lvl;
};
typedef struct Node node;
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
	{	(*t)=z;z->l=0;}
	else if ((z->data) <= (y->data))
		y->l=z;
	else
		y->r=z;
	int tab;
}

node* findmin(node **t)
{
	if((*t)->l!=NULL)
		return findmin(&((*t)->l));
	else
	{
                node *p=*t;
                return p;
        }

}

node* srch(node **t,int x,int lvl1)
{
	if(*t==NULL)
	{
		node *z=NULL;
		return z;
	}
	else
	{
		if((*t)->data > x)
			srch(&((*t)->l),x,lvl1+1);
		else if((*t)->data < x)
			srch(&((*t)->r),x,lvl1+1);
		else if((*t)->data==x)
		{
			node *z=*t;
			return z;
		}
	}
}

node* findmax(node **t)
{
        if((*t)->r!=NULL)
                return findmax(&((*t)->r));
        else
	{
		node *p=*t;
		return p;
	}
}
node* suc(node **t)
{	
	
	if((*t)->r!=NULL)
		return findmin(&((*t)->r));
	node *x=*t;
	node *y=x->p;
	while(y!=NULL && x==y->r)
	{
		x=y;
		y=y->p;
	}
	return y;
}
node* pre(node **t)
{
        if((*t)->l!=NULL)
                return findmax(&((*t)->r));
        node *x=*t;
        node *y=x->p;
        while(y!=NULL && x==y->l)
        {
                x=y;
                y=y->p;
        }
        return y;
	int tab;
}
void del(node **t,node **l)
{
	node *z=*l;
	node *y=NULL;
	node *x=NULL;
	if(z->l==NULL || z->r==NULL)
		y=z;
	else
		y=suc(&z);
	if(y->l!=NULL)
		x=y->l;
	else
		x=y->r;
	if(x!=NULL)
		x->p=y->p;
	if(y->p==NULL)
		*t=x;
	else if(y==(y->p)->l)
		(y->p)->l=x;
	else
		(y->p)->r=x;
	if(y!=z)
	{
		z->data=y->data;
		if(z->p==NULL)
			y->p=NULL;
	}
	
}

void inorder(node **t)
{
	if(*t==NULL)
		return ;
	else
	{
		node *q=*t;
		inorder(&(q->l));
		printf("%d ",q->data);
		inorder(&(q->r));
	}
}
void preorder(node **t)
{
        if(*t==NULL)
                return ;
        else
        {
                node *q=*t;
		printf("%d ",q->data);
                preorder(&(q->l));
                preorder(&(q->r));
        }
}
void postorder(node **t)
{
        if(*t==NULL)
                return ;
        else
        {
                node *q=*t;
                postorder(&(q->l));
                postorder(&(q->r));
		printf("%d ",q->data);
        }
}
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
}
void main()
{
	node *t=NULL;
	char ch[10];
	do{
		scanf("%s",ch);
		if(strcmp(ch,"insr")==0)
		{
			int n;
			scanf("%d",&n);
			insert(&t,n);
		}
		else if(strcmp(ch,"srch")==0)
		{
			int n;
			scanf("%d",&n);
			if(t==NULL)
			{
				printf("NOT FOUND\n");
				continue;
			}
			node *z=srch(&t,n,0);
			if(z==NULL)
				printf("NOT FOUND\n");
			else
				printf("FOUND\n");
		}
		else if(strcmp("minm",ch)==0)
		{
			if(t==NULL)
				printf("NIL\n");
			else
			{
				node*x=findmin(&t);
				printf("%d\n",x->data);
			}
		}
		else if(strcmp(ch,"maxm")==0)
		{
			if(t==NULL)
                                printf("NIL\n");
                        else
                        {
                                node*x=findmax(&t);
                                printf("%d\n",x->data);
                        }
		}
		else if(strcmp(ch,"pred")==0)
		{
			int n;
			scanf("%d",&n);
			if(t!=NULL)
			{
			node *x=findmin(&t);
			
			node *z=srch(&t,n,0);
			
			if(z==NULL)
				printf("NULL\n");
			else 
			{
				node *y=pre(&z);
				if(y==NULL)
					printf("-1\n");
				else
					printf("%d\n",y->data);
			}
			}
			else
				printf("NULL\n");

		}
		else if(strcmp(ch,"succ")==0)
		{
			int n;
                        scanf("%d",&n);
			if(t!=NULL)
			{
                        node *x=findmax(&t);
			
                        node *z=srch(&t,n,0);
			
                        if(z==NULL||t==NULL)
                                printf("NULL\n");
                        else
                        {
                                node *y=suc(&z);
                                if(y==NULL)
                                        printf("-1\n");
                                else
                                        printf("%d\n",y->data);
                        }
                	}
			else
				printf("NULL\n");
		}
		else if(strcmp(ch,"delt")==0)
		{
			int n;
			scanf("%d",&n);
			if(t==NULL)
			{
				printf("NULL\n");
				continue;
			}
			node *z=srch(&t,n,0);
			if(z==NULL)
				printf("-1\n");
			else
				del(&t,&z);
		}
		else if(strcmp(ch,"inor")==0)
		{
			inorder(&t);
			printf("\n");
		}
		else if(strcmp(ch,"prer")==0)
		{
			preorder(&t);
			printf("\n");
		}
		else if(strcmp(ch,"post")==0)
		{
			postorder(&t);
			printf("\n");
		}
		else if(strcmp(ch,"prep")==0)
		{
			paren(&t);
			printf("\n");
		}
		else if(strcmp(ch,"stop")==0)
			exit(0);
	}while(1);
}

