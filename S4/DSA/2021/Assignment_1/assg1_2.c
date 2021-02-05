#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left ;
    struct Node *right ;
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

    // printf("O[%d %c] ",i,ch[0]) ;
 	if(scanf("%d",&n))
	{
		// scanf("%c",&c) ;
        // printf("{%d} ",n) ;
		Node *t  = (Node*) calloc(1,sizeof(Node)) ;
		t->key = n ;

        // printf("\nLeft") ;
		t->left = Create() ;
        // printf("\nRight") ;
		t->right = Create() ;
		temp = t;
	}
	c = getchar() ;
    // printf("C[%d %c] ",i,ch[0]) ;
	return temp ;
}

void main() 
{
    char op ;
    int x ;
    int i = 0 ;
    Node *Tree = NULL ;
    Tree = Create() ;
    parenPrint(Tree) ;
    printf("\n") ;
    /*
    do 
    {
        scanf(" %c",&op) ;
        // printf("Scanned %c\n",op) ;
        switch(op) 
        {
            case 'i' :  if(i==0) 
                            Tree = calloc(1,sizeof(Node)) ;
                        else 
                            Tree = realloc(Tree,(i+1) * sizeof(Node)) ;
                        scanf("%d",&(Tree[i].key)) ;
                        // printf("Scanned [%#x] %d\n",Tree + i,Tree[i].key) ;
                        Tree[i].left = NULL ;
                        Tree[i].right = NULL ;
                        if(i>0)
                        {
                            if(i%2)
                                Tree[(i-1)/2].left = Tree + i ;
                            else 
                                Tree[(i-2)/2].right = Tree + i ;
                        }
                        i += 1 ;
                        break ;
            case 'p' :  parenPrint(Tree) ;
                        printf("\n");
                        break ;
            case 'e' :  break ;
            default  :  break ; 
        }
    } while(op != 'e') ;
    */
}