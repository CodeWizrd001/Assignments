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

void mirror(node **t)
{
	if(*t==NULL)
		return;
	else
	{	
		mirror(&((*t)->l));
		mirror(&((*t)->r));
		node *tm=(*t)->l;
		(*t)->l=(*t)->r;
		(*t)->r=tm;
	}
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
	int tab;
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
	char ch;char *s;int top=-1,f=0;
	while(scanf("%c",&ch))
	{
		top++;
		*(s+top)=ch;
		if(ch=='(')
			f++;
		else if(ch==')')
			f--;
		if(f==0)
			break;
	}
	node *t=NULL;
	for(int i=0;i<=top;i++)
	{	
		if(!(s[i]==')'||s[i]=='('||s[i]==' '))
		{
			int n=0;
			while(s[i]>='0'&&s[i]<='9')
			{
				n=10*n+(int)(s[i])-48;
				i++;
				if(i==top)
					break;
			}
			insert(&t,n);
		}
	}
	mirror(&t);
	paren(&t);
	printf("\n");
}
