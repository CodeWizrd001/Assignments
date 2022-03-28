#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

FILE *Fin ;
FILE *Fout ;

typedef struct Node 
{
	struct Node *lC ;
	struct Node *rC ;
	int val ;
	char color ;
} Node ;

int search(Node *tree,int e)
{
	if(tree==NULL)
		return 0; 
	else if(tree->val==e)
		return 1 ;
	else if(tree->val>e)
		return search(tree->lC,e) ;
	else 
		return search(tree->rC,e) ;
}

Node* searchPos(Node* tree, int element)
{
    if(tree == NULL || tree->val == element) return tree;
    else if(tree->val > element) 
        return searchPos(tree->lC, element);
    else 
        return searchPos(tree->rC, element);
}

int height(Node *) ;

int ht(Node *x)
{
	if(x==NULL)
		return -1 ;
	return height(x) ;
}

int height(Node* tree)
{
	if(tree==NULL)
		return -1 ;
	int hl = height(tree->lC) ;
	int hr = height(tree->rC) ;
	int x = hr > hl ? hr : hl ;
	return 1 + x ;
}

int bHeight(Node* tree)
{
	if(tree==NULL)
		return 1  ;
	int hl = bHeight(tree->lC) ;
	int hr = bHeight(tree->rC) ;
	int x = hr > hl ? hr : hl ;
	if(tree->color=='B')
		return 1 + x ;
	return x ;
}

Node *leftRotate(Node *tree)
{
	if(tree==NULL)
		return NULL ;
	Node *x = tree->rC ;
	if(x==NULL)
		return tree ;
	Node *y = x->lC ;
	x->lC = tree ;
	tree->rC = y ;
	return x ;
}

Node *rightRotate(Node *tree)
{
	if(tree==NULL)
		return NULL ;
	Node *x = tree->lC ;
	if(x==NULL)
		return tree ;
	Node *y = x->rC ;
	x->rC = tree ;
	tree->lC = y ;
	return x ;
}

int findMin(Node *tree)
{
	if(tree==NULL)
		return INT_MAX ;
	else if(tree->lC==NULL)
		return tree->val ;
	else 
		return findMin(tree->lC) ;
}

int findMax(Node *tree)
{
	if(tree==NULL)
		return INT_MIN ;
	else if(tree->rC==NULL)
		return tree->val ;
	else 
		return findMax(tree->rC) ;
}


Node *minNode(Node *tree)
{
	if(tree==NULL)
		return NULL ;
	else if(tree->lC==NULL)
		return tree ;
	else 
		return minNode(tree->lC) ;
}

Node *maxNode(Node *tree)
{
	if(tree==NULL)
		return NULL ;
	else if(tree->rC==NULL)
		return tree ;
	else 
		return maxNode(tree->rC) ;
}

int paren(Node *tree)
{
	int mt ;
	if(tree==NULL)
	{
		fprintf(Fout,"( ) ");
		return 1;
	}
	fprintf(Fout,"( %d %c ",tree->val,tree->color) ;
	mt = paren(tree->lC) ;
	mt = paren(tree->rC) ;
	fprintf(Fout,") ") ;
	return 0 ;
}

Node *Create()
{
	char ch[3] ;
	int n ;
	char c ;
	fscanf(Fin,"%s",ch); 
	if(fscanf(Fin,"%d",&n))
	{
		fscanf(Fin," %c",&c) ;
		Node *temp  = (Node*) calloc(1,sizeof(Node)) ;
		temp->val = n ;
		temp->color = c ;
		temp->lC = Create() ;
		temp->rC = Create() ;
		fscanf(Fin,"%s",ch) ;
		return temp ;
	}
	fscanf(Fin,"%s",ch) ;
	return NULL ;
}

int getBalance(Node *x)
{
	if(x==NULL)
		return 0 ;
	return ht(x->lC)-ht(x->rC) ;
}

char Col(Node *x)
{
	if(x==NULL)
		return 'B' ;
	return x->color ;
}

void print(Node *tree,int key)
{
	if(key==29)
	{
		paren(tree) ;
		printf("\n") ;
	}
}

Node *rbinsert(Node *tree,Node *x)
{
	int key = x->val ;
	Node *y ;
	if(tree == NULL)
		return x ;
	if(key <= tree->val)
	{
		tree->lC = rbinsert(tree->lC,x) ;
		if(tree->lC->color=='R')
		{
			if((Col(tree->lC->lC)=='R')||Col(tree->lC->rC)=='R') 
			{
				if(Col(tree->rC)=='B')
				{
					if(Col(tree->lC->lC)=='R')
					{
						y = rightRotate(tree) ;
						y->rC->color = 'R' ;
						y->color = 'B' ;
						print(tree,key) ;
						return y ;
					}
					else 
					{
						tree->lC = leftRotate(tree->lC) ;
						y = rightRotate(tree) ;
						y->rC->color = 'R' ;
						y->color = 'B' ;
						return y ;
					}
				}
				else
				{
					tree->rC->color = 'B' ;
					tree->lC->color = 'B' ;
					tree->color = 'R' ;
				}
			}
		}
	}
	else 
	{
		tree->rC = rbinsert(tree->rC,x) ;
		if(Col(tree->rC)=='R')
		{
			if((Col(tree->rC->rC)=='R')||Col(tree->rC->lC)=='R') 
			{
				if(Col(tree->lC)=='B')
				{

					if(Col(tree->rC->rC)=='R')
					{
						y = leftRotate(tree) ;
						y->lC->color = 'R' ;
						y->color = 'B' ;
						return y ;
					}
					else 
					{
						tree->rC = rightRotate(tree->rC) ;
						y = leftRotate(tree) ;
						y->lC->color = 'R' ;
						y->color = 'B' ;
						return y ;
					}
				}
				else if(Col(tree->lC)=='R')
				{
					tree->lC->color = 'B' ;
					tree->rC->color = 'B' ;
					tree->color = 'R' ;
				}
			}
		}
	}
	return tree ;
}

Node *RBInsert(Node *tree,int x)
{
	Node *temp = (Node *) calloc(1,sizeof(tree)) ;
	temp->val = x ;
	temp->color = 'R' ;
	temp->lC = NULL ;
	temp->rC = NULL ;
	tree = rbinsert(tree,temp) ;
	if(tree->color=='R')
		tree->color = 'B' ;
	return tree ;
}

void main(int argc,char **argv)
{
	Fin = stdin ;
	Fout = stdout ;
	char ch[10] = "init" ;
	int resp ;
	Node *tree =NULL ; 
	while(!feof(stdin)&&strcmp(ch,"stop")) 
	{
		fscanf(Fin,"%d",&resp) ;
		if(feof(stdin)) 
			break ;
		tree = RBInsert(tree,resp) ;
		paren(tree) ;
		fprintf(Fout,"\n") ;
	}
}
