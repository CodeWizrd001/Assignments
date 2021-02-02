#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
typedef struct node
{
	int data;
	struct node *left,*right;
}node;



node* parent(node* tree,node* temp)
{if(tree->data==temp->data)
	return NULL;
else
{
	while(tree->data!=temp->data)
	{	if(tree->data<temp->data)

		if(tree->right->data==temp->data)
			return tree;
		else 	
			tree=tree->right;
else if(tree->data>temp->data)
		if(tree->left->data==temp->data)
			return tree;
		else
			tree=tree->left;
	}
	}

}


node* insr(node* tree,int k)
{if(tree==NULL)
	{node *nptr;
	nptr=(node*)malloc(sizeof(node));
	nptr->left=NULL;
	nptr->right==NULL;
	nptr->data=k;
	tree=nptr;
	}
int lvl;
else if(tree->data>k)
	tree->left=insr(tree->left,k);

else if(tree->data<k)
	tree->right=insr(tree->right,k);
return tree;
}
	

void srch(node *tree,int k)
{
	
if(tree==NULL)
	printf("NOT FOUND\n");
else if(tree->data>k)
	srch(tree->left,k);
else if(tree->data<k)
	srch(tree->right,k);
else if(tree->data==k)
	printf("FOUND\n");
}




void maxm(node*tree)
{if(tree==NULL)
        printf("NIL\n");
else
{while(tree->right!=NULL)
        tree=tree->right;
printf("%d\n",tree->data);
}
}

void minm(node*tree)
{if(tree==NULL)
	printf("NIL\n");
else
{while(tree->left!=NULL)
	tree=tree->left;
printf("%d\n",tree->data);
}
}



void pred(node* root,node* tree,int k)
{node *temp=tree;
	if(tree!=NULL)
	{while(tree->data!=k)
		{if(tree->data>k)
		tree=tree->left;
		else if(tree->data<k)
		tree=tree->right;
		if(tree==NULL)
			break;
		}
	if(tree==NULL)
	{	printf("NULL\n");
	
	}
	else
		{if(tree->left!=NULL)
				maxm(tree->left);
		else if(tree->left==NULL&&parent(root,tree)==NULL)
			printf("-1\n");
		else if(tree->left==NULL&&tree->data<temp->data)
			printf("-1\n");
		else
		{
		node *y=parent(root,tree);
		node *x=tree;
		while((parent(root,y)!=NULL)&&(y->left)->data==x->data)
		{x=y;
		y=parent(root,y);
		}
			
		printf("%d\n",y->data);
		}
		}

	}
	else if(tree==NULL)
	printf("NULL\n");	
}



void succ(node *root,node* tree,int k)
{node *temp=tree;
	if(tree!=NULL)
	{while(tree->data!=k)
		{if(tree->data>k)
		tree=tree->left;
		else if(tree->data<k)
		tree=tree->right;
		if(tree==NULL)
			break;
		}
	if(tree==NULL)
		printf("NULL\n");
	
	else
		{if(tree->right!=NULL)
				minm(tree->right);
		else if(tree->right==NULL&&parent(root,tree)==NULL)
			printf("-1\n");
		else if(tree->right==NULL&&parent(root,tree)->data<tree->data)
			printf("-1\n");
		else
		{
		node *y=parent(root,tree);
		node *x=tree;
		while((parent(root,y)!=NULL)&&y->data<x->data)
		{x=y;
		y=parent(root,y);
		}
			
		printf("%d\n",y->data);
		}
		}

	}
	else if(tree==NULL)
	printf("NULL\n");	
}




node* delt(node* root,node* tree,int k)	
{ node *temp=tree;
	if(tree!=NULL)           
	{while(tree->data!=k)   
		{if(tree->data>k)   
		tree=tree->left;    
		else if(tree->data<k)      
		tree=tree->right; 
	  if(tree==NULL)
	  	break;	  
		}       
	     	if(tree==NULL)
				printf("NULL\n");
					
		else
		{node *x,*y;
			if(tree->left==NULL||tree->right==NULL)
				y=tree;
			else
			{if(tree->right!=NULL)
				{	while(tree->right!=NULL)
						tree=tree->right;
						y=tree;
				}
			else

			{        
				node *y1=parent(root,tree);     
				node *x1=tree;    
				while((parent(root,y1)!=NULL)&&y1->data<x1->data)     
				{x1=y1;
				y1=parent(root,y1);   
				} 
				y=y1;
			}
			}
		

		if(y->left!=NULL)
			x=y->left;
		else
			x=y->right;
		if(parent(root,y)==NULL)
			temp=x;
		else if(y==parent(root,y)->left)
			parent(root,y)->left=x;
		else
			parent(root,y)->right=x;
		if(y!=tree)
			tree->data=y->data;
	
		}
	
	}
	else if(tree==NULL)
		printf("NULL\n");
return temp;
}


void inor(node* tree)
{
	if(tree!=NULL)
	{
		inor(tree->left);
		printf("%d ",tree->data);
		inor(tree->right);
	}
}


void prer(node* tree)
{
	if(tree!=NULL)
        {
        	printf("%d ",tree->data);
        	prer(tree->left);
		prer(tree->right);
        }
}


void post(node* tree)
{
	if(tree!=NULL)
        {
        	post(tree->left);
        	post(tree->right);
		printf("%d ",tree->data);
        }
}


int main()
{
	node *tree;
	tree=NULL;
	char a[50];
	scanf("%s",a);
	while(strcmp(a,"stop")!=0)
	{
		int k;
		if(strcmp(a,"insr")==0)
		{
			scanf("%d",&k);
			tree=insr(tree,k);
		}
		else if(strcmp(a,"srch")==0)
		{
			scanf("%d",&k);
			srch(tree,k);
		}
		else if(strcmp(a,"minm")==0)
		{
			minm(tree);
		}
	
		else if(strcmp(a,"maxm")==0)
		{
			maxm(tree);
		}

		else if(strcmp(a,"pred")==0)
                {
			scanf("%d",&k);
			pred(tree,tree,k);
                }  
		else if(strcmp(a,"succ")==0)
                {
			scanf("%d",&k);
			succ(tree,tree,k);
                }
	
		else if(strcmp(a,"delt")==0)
                {
			scanf("%d",&k);
			tree=delt(tree,tree,k);
                }
		
		else if(strcmp(a,"inor")==0)
                {
			inor(tree);
			printf("\n");
                }
		else if(strcmp(a,"prer")==0)
                {
			prer(tree);
			printf("\n");
                }
		else if(strcmp(a,"post")==0)
                {
			post(tree);
			printf("\n");
                }

		scanf("%s",a);
}
}
