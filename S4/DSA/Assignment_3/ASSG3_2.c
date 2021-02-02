#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define bool int
typedef struct Node Node;
struct Node{
        int key;
        Node* left;
        Node* right;
};
int max(int a,int b)
{ 
	if(a>b)
		return a;
	else 
		return b;
}
/*Node* new_node(int data)//
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->key = data;
	new_node->right = new_node->left = NULL;
	return new_node;
}*/
Node* insert(Node* root)//node = root
{
	char c;
	int n;
	scanf(" %c",&c);
	if(scanf("%d",&n)==1)
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->key = n;
		new_node->left = new_node->right = NULL;
		root = new_node;
		root->left =insert(root->left);
		root->right = insert(root->right);
		scanf(" %c",&c);
		return root;
	}
	else
	{
		scanf(" %c",&c);
		return NULL;
	}		
}
int isBST(Node* node)
{
  if (node == NULL)
    return 1;

  if (node->left != NULL && node->left->key > node->key)
    return 0;

  if (node->right != NULL && node->right->key < node->key)
    return 0;

  if (!isBST(node->left) || !isBST(node->right))
    return 0;

  return 1;
}
int height(Node* T)
{
	if(T == NULL)
		return 0;
	else
		return max(height(T->left),height(T->right)) +1;
}

int isAVL(Node* root) 
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
int main()
{	
	Node *tree = NULL;
	tree = insert(tree);
	if(isAVL(tree)==1 && isBST(tree)==1)
			printf("1\n");
	else 
			printf("0\n");
	return 0;
}
