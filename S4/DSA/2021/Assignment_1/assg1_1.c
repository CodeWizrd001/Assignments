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

void main() 
{
    char op ;
    int x ;
    int i = 0 ;
    Node *Tree = NULL ;
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
}