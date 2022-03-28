#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<limits.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right; 
}Node;

Node *getNode(int key);
Node *preorder(Node *x);
Node *postorder(Node *x);
Node *inorder(Node *x);
void prep(Node *tree);
int counter_index(char *string,int start_index,int end_index);
Node *decode_bt(char *string,int start_index,int end_index);
int findMaxBST(Node *tree,int *isBST,int *MAXI,int *MINI,int *size);
int maxSubBST(Node *tree);



int main()
{
	int len=0,lens=0;
	Node *T=NULL;
	char str[1000];
	char string[1000];
	scanf("%[^\n]s",str);
	while(str[lens]!='\0')
	{
		if(str[lens]!=' ')
		{
			string[len]=str[lens];
			len++;
		}
		lens++;
	}
	T=decode_bt(string,1,len-2);
	maxSubBST(T);
	
}


Node *decode_bt(char *string,int start_index,int end_index)
{
	//printf("\n start index=%d......end_index=%d\n",start_index,end_index);
	if(start_index>end_index)
		return NULL;
	//int key=string[start_index]-'0';
	int number,place,digit;
	int j=start_index,flag=0;
	//if(isdigit(string[j])!=0)
	//{
	//printf("string[j-1]=%c\n",string[j-1]);
	if(string[j]=='-')
	{
		flag=1;
		j++;
		//printf("it is -\n");
	}
	//if(string[j]=' ')
		//j++;
	number=0;
	place=1;
	while(isdigit(string[j])!=0)
	{
		//printf("%c",string[j]);
		digit=string[j]-'0';
		number=number*place+digit;
		place=place*10;
		j++;
	}
		//printf("\n%d\n",number);
		//T=insert(T,number);
	//}
	start_index=j-1;
	//printf("-----------------number=%d--------------\n",number);
	if(flag==1)
		number=-number;
	//printf("------------------------number=%d---------------------\n",number);

	Node *T=getNode(number);
	int index=-1;
	if((start_index+1<=end_index)&&(string[start_index+1]=='('))
		index=counter_index(string,start_index+1,end_index);
	//printf("\nindex=%d\n",index);
	if(index!=-1)
	{
		T->left=decode_bt(string,start_index+2,index-1);
		T->right=decode_bt(string,index+2,end_index-1);
	}
	return T;
}

int counter_index(char *string,int start_index,int end_index)
{
	//printf("\nentered counter_index\n");
	int len=end_index-start_index+1;
	int s[len];
	int top=-1;
	for(int i=start_index;i<=end_index;i++)
	{
		//printf("string[%d]=%c\n",i,string[i]);
		if(string[i]=='(')
		{
			top++;
			s[top]=string[i];
		}
		else if(string[i]==')')
		{
			if(s[top]=='(')
				top--;
			if(top==-1)
				return i;
		}


	}
	return -1;
}
int maxSubBST(Node *tree)
{
	//printf("enter the maxBST\n");
	int isBST=0,MAXI=INT_MIN,MINI=INT_MAX,size=0;
	findMaxBST(tree,&isBST,&MAXI,&MINI,&size);
	printf("%d\n",size);
}

int findMaxBST(Node *tree,int *isBST,int *MAXI,int *MINI,int *size)
{
	//printf("------------------------------------enter the findBST-----------------\n");
	if(tree==NULL)
	{
		*isBST=1;
		return 0;
	}
	int left_size=0,right_size=0,lflag=0,rflag=0;
	int min=INT_MAX;
	*MAXI=INT_MIN;
	//printf("Values BEFORE going inside left of %d\n",tree->key);
	//printf("MAXI=%d....MINI=%d\n",*MAXI,*MINI);
	left_size=findMaxBST(tree->left,isBST,MAXI,MINI,size);
	if((*isBST==1)&&(tree->key>*MAXI))
		lflag=1;
	min=*MINI;


	*MINI=INT_MAX;
	//printf("Values BEFORE going inside right of %d\n",tree->key);
        //printf("MAXI=%d....MINI=%d\n",*MAXI,*MINI);

	right_size=findMaxBST(tree->right,isBST,MAXI,MINI,size);
	if((*isBST==1)&&(tree->key<*MINI))
		rflag=1;
	//printf("Values AFTER going right\n");
        //printf("MAXI=%d....MINI=%d\n",*MAXI,*MINI);

	if(min<*MINI)
		*MINI=min;
	if(tree->key<*MINI)
		*MINI=tree->key;
	if(tree->key>*MAXI)
		*MAXI=tree->key;
	//printf("UPDATED values after if case\n");
        //printf("MAXI=%d....MINI=%d\n",*MAXI,*MINI);


	if((lflag==1)&&(rflag==1))
	{
		if (left_size+right_size+1>*size)
			*size=left_size+right_size+1;
		//printf("size=%d\n",*size);
		return left_size+right_size+1;
	}
	else
	{
		*isBST=0;
		return 0;
	}
}

Node *getNode(int key)
{
	Node *newNode=(Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
	
Node *inorder(Node *x)
{
	if(x!=NULL)
	{
		inorder(x->left);
		printf("%d ",x->key);
		inorder(x->right);
	}
}

Node *preorder(Node *x)
{
        if(x!=NULL)
        {
                printf("%d ",x->key);
		preorder(x->left);
                preorder(x->right);
        }
}

Node *postorder(Node *x)
{
        if(x!=NULL)
        {
                postorder(x->left);
                postorder(x->right);
		printf("%d ",x->key);
        }
}
void paren(Node *tree)
{
	if(tree==NULL)
		return;
	if((tree->left==NULL)&&(tree->right==NULL))
	{
		//printf("(");
		printf("( %d ( ) ( ) ) ",tree->key);
		return;
		//printf("()())");
	}
	
	printf("( ");
	printf("%d ",tree->key);
	if(tree->left==NULL)
	{
		printf("( ) ");
	}

	paren(tree->left);
	//printf(")");
	if(tree->right==NULL)
		printf("( ) ");
	if(tree->right!=NULL)
	{
		//printf("(");
		paren(tree->right);
		//printf(")");
	}
	printf(") ");
}
