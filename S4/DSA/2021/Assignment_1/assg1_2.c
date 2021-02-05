#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left ;
    struct Node *right ;
    int level ;
    int key ;
} Node ;

void parenPrint(Node *Root) 
{
    if(Root == NULL || Root == 0) 
    {
        printf("()") ;
        return ;
    }
    Node *l = Root->left ;
    Node *r = Root->right ;
    // printf("[%#x %#x %#x]",Root,l,r) ;
    printf("(%d",Root->key) ;
    // printf("%#x %d\n",l,l==NULL) ;
    parenPrint(l) ; 
    parenPrint(r) ;
    printf(")") ;
    return ;
}

Node *Search(Node *Tree,int key)
{
    if(Tree == NULL)
        return NULL ;
    if(Tree->key == key) 
        return Tree ;
    Node *res = Search(Tree->left,key) ;
    if(res!=NULL) 
        return res ;
    else 
        return Search(Tree->right,key) ;
}

Node *Create()
{
    Node *temp = NULL ;    
	char ch[3] ;
	int n ;
	char c ;
	c = getchar() ;
 	if(scanf("%d",&n))
	{
		Node *t  = (Node*) calloc(1,sizeof(Node)) ;

		t->key = n ;
		t->left = Create() ;
		t->right = Create() ;

		temp = t;
	}
	c = getchar() ;
	return temp ;
}

Node *Parent(Node *node,Node *Tree) 
{
    if(Tree == node || Tree == NULL)
        return NULL ;
    if(Tree->left == node || Tree->right == node) 
        return Tree ;

    Node *res = Parent(node,Tree->left) ;

    if(res!=NULL) 
        return res ;
    else 
        return Parent(node,Tree->right) ;
}

void Levels(Node *Tree,int level) 
{ 
    if(Tree == NULL) 
        return ;
    
    Tree->level = level ;

    Levels(Tree->left,level+1) ;
    Levels(Tree->right,level+1) ;
}

int cousinExist()
{
    return 0 ;
}

int cousinPrint(Node *Tree,Node *parent,int level) 
{
    if(Tree == NULL || Tree == 0 || Tree == parent)
        return 0 ;
    
    Node *l = Tree->left ;
    Node *r = Tree->right ;

    if(Tree->level == level)
    {
        printf("%d ",Tree->key) ;
        return 1 ;
    }

    int x = cousinPrint(l,parent,level) ; 
    int y = cousinPrint(r,parent,level) ; 

    return x || y ;
}

void main() 
{
    int x ;

    Node *Tree = NULL ;
    Tree = Create() ;
    // printf("Check -2\n") ;
    Levels(Tree,0) ;
    // printf("Check -1\n") ;

    scanf("%d",&x) ;
    // printf("Check 0") ;
    Node *n = Search(Tree,x) ;
    // printf("Check 1") ;
    Node *parent = Parent(n,Tree) ;
    // printf("Check 2") ;
    if(n->level == 0 || n->level == 1) 
        printf("-1\n") ;
    else 
    {
        if(!cousinPrint(Tree,parent,n->level))
            printf("-1\n") ;
        else 
            printf("\n") ;
    }
}