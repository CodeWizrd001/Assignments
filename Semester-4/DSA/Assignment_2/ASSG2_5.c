#include<stdio.h>
#include<stdlib.h>
struct Node 
{
	int data;
	struct Node *l;
	struct Node *r;
	int lvl;
	int path;
};

typedef struct Node node ;
void insert(node **t,int e,int lvl1)
{
        node *z=(node*)malloc(sizeof(node));
        z->data=e;
        z->l=NULL;
        z->r=NULL;
	z->lvl=lvl1;
	(*t)=z;
}

int longest(node **t,int h)
{
	if((*t)==NULL)
		return 1;
	else
	{
		int l=h-(*t)->l->lvl;
		int r=h-(*t)->r->lvl;
		(*t)->path=l+r+1;
		
		if((*t)->path>(*t)->l->path&&(*t)->path>(*t)->r->path)
			return (*t)->path;
		else if((*t)->r->path>(*t)->l->path)
			return (*t)->r->path;
		else 
			return (*t)->l->path;
	}
	int tab;
}

void paren(node **t)
{
        if((*t)!=NULL)
        {
                printf("(%d  ",(*t)->lvl);
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
int Node(node **t,char s[],int top,int i,int lvl)
{
	if(s[i]=='(')
	{
		int n=0;i++;int f=1,sym=1;
                while(s[i]>='0'&&s[i]<='9'||s[i]=='-')
                {
			if(s[i]=='-'&&f)
			{	f=0;
				sym*=-1;
				i++;
			}
	                 n=10*n+(int)(s[i])-48;
                         i++;
                         if(i==top)
        	                 break;
                }
		n*=sym;
		insert(&(*t),n,lvl);
		n=0;
		if(i!=top&&s[i]=='('&&s[i+1]==')')
		{
			(*t)->l=NULL;
			i=i+2;
		}
		else
		{
			i=Node(&((*t)->l),s,top,i,lvl+1)+1;
		}
		if(i!=top&&s[i]=='('&&s[i+1]==')')
                {
                        (*t)->r=NULL;
                        i=i+2;
                }
		else
                {
                        i=Node(&((*t)->r),s,top,i,lvl+1)+1;
                }
		return i;
	}
	
}
int height(node **t)
{
	if(*t==NULL)
		return -1;
	else
	{
		int x=height(&(*t)->l);
		int y=height(&(*t)->r);
		return x>y?x+1:y+1;
	}
}

void main()
{
        char ch;char *s=(char*)malloc(sizeof(char));int top=-1,f=0;
        while(scanf("%c",&ch))
        {
		if(ch!=' ')
		{top++;
                *(s+top)=ch;
                if(ch=='(')
                        f++;
                else if(ch==')')
                        f--;
                if(f==0)
                        break;
		}
        }
	node *t=NULL;
	Node(&t,s,top,0,0);
	int h=height(&t);
	int p=longest(&t,h);
	printf("%d ",h);
	printf("%d",p+1);
}
