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
		return 0 ;
	int hl = bHeight(tree->lC) ;
	int hr = bHeight(tree->rC) ;
	int x = hr > hl ? hr : hl ;
	if(tree->color=='B')
		return 1 + x ;
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
	
int ht(Node *x)
{
	if(x==NULL)
		return -1 ;
	return bHeight(x) ;
}

int getBalance(Node *x)
{
	if(x==NULL)
		return 0 ;
	return ht(x->lC)-ht(x->rC) ;
}

int isrb(Node*) ;

int isRBTree(Node *tree)
{
	if(tree==NULL)
		return 1 ;
	else if(tree->color=='R')
		return 0 ;
	else 
		return isrb(tree) ;
}

int isrb(Node *tree)
{
	if(tree==NULL) 
		return 1 ;
	int avl , avr , bst , y , z ;
	bst = 0 ;
	avl = isrb(tree->lC) ;
	avr = isrb(tree->rC) ;
	y = findMax(tree->lC) ;
	z = findMin(tree->rC) ;
	if(y<=tree->val&&z>tree->val)
		bst = 1 ;
	int x = getBalance(tree) ;
//	printf("key : %-3d bst : %d avl : %d avr : %d bal : %d\n",tree->val,bst,avl,avr,x) ;
	if(tree->color=='R')
	{
		if(tree->lC&&tree->rC)
		{
			if(tree->lC->color=='R'||tree->rC->color=='R')
				return 0 ;
		}
		else if(tree->lC)
		{
			if(tree->lC->color=='R')
				return 0 ;
		}
		else if(tree->rC)
		{
			if(tree->rC->color=='R')
				return 0 ;
		}
	}
	if(avl&&avr&&bst)
		if(x==0)
			return 1 ;
	return 0 ;
}

void main(int argc,char **argv)
{
	Fin = stdin ;
	Fout = stdout ;
	char ch[10] = "init" ;
	int resp ;
	Node *tree = Create() ;
//	paren(tree) ;
//	fprintf(Fout,"\n") ;
	fprintf(Fout,"%d\n",isRBTree(tree)) ;
}
