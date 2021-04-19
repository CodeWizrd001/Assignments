#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool int 
typedef struct node
{
	int data;
	struct node *left,*right;
	int ht;				
}node; 
 
node *insert(node *,int);
node *deleteNode(node *,int);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
int isAVL(node *);
void printTree(node *);
node* search(node *,int);
int main()
{
	node *tree;
	tree=NULL;
	char a[50];
	scanf("%s",a);
	int k;
	while(strcmp(a,"stop")!=0)
	{
		if(strcmp(a,"insr")==0)
		{
			scanf("%d",&k);
			tree=insert(tree,k);
		}
		else if(strcmp(a,"srch")==0)
		{
			scanf("%d",&k);
			if(search(tree,k)!=NULL)
			{
				printf("TRUE\n");
			}
			else 
				printf("FALSE\n");
		}
		else if(strcmp(a,"delt")==0)
                {
			scanf("%d",&k);
			tree=deleteNode(tree,k);
                }
		else if(strcmp(a,"disp")==0)
		{
			printTree(tree);
			printf("\n");
		}
		else if(strcmp(a,"avlc")==0)
		{
			if(isAVL(tree)==1)
				printf("TRUE\n");
			else 
				printf("FALSE\n");
		}
		else if(strcmp(a,"pbal")==0)
		{
			scanf("%d",&k);
			printf("%d",BF(search(tree,k)));
		}
		else if(strcmp(a,"stop")==0)
		{
			break;
		}
			
		scanf("%s",a);
	}
	return 0;

}
 
node * insert(node *T,int x)
{
	if(T==NULL)
	{
		T=(node*)malloc(sizeof(node));
		T->data=x;
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(x > T->data)		
		{
			T->right=insert(T->right,x);
			if(BF(T)==-2)
				if(x>T->right->data)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(x<T->data)
			{
				T->left=insert(T->left,x);
				if(BF(T)==2)
					if(x < T->left->data)
						T=LL(T);
					else
						T=LR(T);
			}
		
		T->ht=height(T);
		
		return(T);
}
 
node * deleteNode(node *T,int x)
{
	node *p;
	
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(x > T->data)		// insert in right subtree
		{
			T->right=deleteNode(T->right,x);
			if(BF(T)==2)
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else
			if(x<T->data)
			{
				T->left=deleteNode(T->left,x);
				if(BF(T)==-2)	//Rebalance during windup
					if(BF(T->right)<=0)
						T=RR(T);
					else
						T=RL(T);
			}
			else
			{
				//data to be deleted is found
				if(T->right!=NULL)
				{	//delete its inorder succesor
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					T->data=p->data;
					T->right=deleteNode(T->right,p->data);
					
					if(BF(T)==2)//Rebalance during windup
						if(BF(T->left)>=0)
							T=LL(T);
						else
							T=LR(T);\
				}
				else
					return(T->left);
			}
	T->ht=height(T);
	return(T);
}
 
int height(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
	
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
		
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	
	if(lh>rh)
		return(lh);
	
	return(rh);
}
 
node * rotateright(node *x)
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
 
node * rotateleft(node *x)
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	
	return(y);
}
 
node * RR(node *T)
{
	T=rotateleft(T);
	return(T);
}
 
node * LL(node *T)
{
	T=rotateright(T);
	return(T);
}
 
node * LR(node *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	
	return(T);
}
 
node * RL(node *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}
 
int BF(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
 
	return(lh-rh);
}
bool isAVL(struct node* root) 
{ 
    int lh; 
    int rh; 
  
    if (root == NULL) 
        return 1; 
  
    lh = height(root->left); 
    rh = height(root->right); 
  
    if (abs(lh - rh) <= 1 && isAVL(root->left) && isAVL(root->right)) 
        return 1; 
  
    return 0; 
} 
void printTree(node* root)
{
	printf("( ");
	if(root!=NULL)
	{
		printf("%d ",root->data);
		printTree(root->left);
		printTree(root->right);
	}
	printf(") ");	
}
node* search(node* root, int key)//normal search
{
	if (root == NULL || root->data == key)
		return root;

	if (root->data < key)
		return search(root->right, key);

	return search(root->left, key);
	
}

