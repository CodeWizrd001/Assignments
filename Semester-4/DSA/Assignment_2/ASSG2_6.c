#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{
	int key;
	int sum;
	struct node *left;
	struct node *right;
}node;

node *getNode(int key);
node *preorder(node *x);
node *postorder(node *x);
node *inorder(node *x);
void paren(node *tree);
int counter_index(char *string,int start_index,int end_index);
node *decode_bt(char *string,int start_index,int end_index);
int sumTree(node **t);
void mod_tree(node *tree);


int main()
{
	int len=0,lens=0;
	node *T=NULL;
	char string[1000];
	char str[1000];
	scanf("%[^\n]s",str);
	while(str[lens]!='\0')
	{
		if(str[lens]!=' ')
		{
			string[len]=str[lens];
			len++;
		}
		//printf("string[len]=%c\n",string[len]);
		lens++;
	}
	T=decode_bt(string,1,len-2);
	sumTree(&T);
	//printf("t->left->sum=%d\n",T->left->sum);
	//printf("t->right->sum=%d\n",T->right->sum);
	mod_tree(T);
	//printf(")");
}


node *decode_bt(char *string,int start_index,int end_index)
{
	//printf("\n start index=%d......end_index=%d\n",start_index,end_index);
	int temp;
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

	node *T=getNode(number);
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


node *getNode(int key)
{
	node *newNode=(node*)malloc(sizeof(node));
	newNode->key=key;
	newNode->sum=key;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

int sumTree(node **t)
{
	/*if(t==NULL||((t->left->left==NULL)&&(t->right->right==NULL)))
		return t;
	t=sumTree(t->left);
	//t->sum+=t->left->sum;
	t=sumTree(t->right);*/
	//node *tree=*t;
	node *temp=*t;
	if(temp==NULL)
		return 0;
	temp->sum=sumTree(&(temp->left))+sumTree(&(temp->right))+temp->sum;
	//printf("before *t->sum=%d\n",(*t)->sum);
	//*t=temp;
	//(*t)->sum=temp->sum;
	//printf("after *t->sum=%d\n",(*t)->sum);
	//printf("temp->sum=%d\n",temp->sum);
	return temp->sum;
}

	
node *inorder(node *x)
{
	if(x!=NULL)
	{
		inorder(x->left);
		printf("%d ",x->key);
		inorder(x->right);
	}
}

node *preorder(node *x)
{
//	printf("Entered preorder\n");
        if(x!=NULL)
        {
                printf("%d ",x->key);
		preorder(x->left);
                //printf("%d ",x->key);
                preorder(x->right);
        }
}

node *postorder(node *x)
{
        if(x!=NULL)
        {
                postorder(x->left);
                //printf("%d ",x->key);
                postorder(x->right);
		printf("%d ",x->key);
        }
}


void mod_tree(node *tree)
{
	if(tree==NULL)
		return;
	if((tree->left==NULL)&&(tree->right==NULL))
	{
		//printf("(");
		printf("( %d ( ) ( ) )",tree->sum);
		return;
		//printf("()())");
	}

	int b;	
	printf("( ");
	printf("%d",tree->sum);
	if(tree->left==NULL)
	{
		printf("( ) ");
	}

	mod_tree(tree->left);
	//printf(")");
	if(tree->right==NULL)
		printf("( ) ");
	if(tree->right!=NULL)
	{
		//printf("(");
		mod_tree(tree->right);
		//printf(")");
	}
	printf(") ");
}

