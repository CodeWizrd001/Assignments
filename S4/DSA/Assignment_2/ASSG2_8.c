#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<limits.h>

typedef struct node
{
	char key;
	int freq;
	struct node *left; 
	struct node *right;
	struct node *next;
}node;



node *getNode(char key,int freq);
node* create(node* head,char value,int freq);
int Sort(node **head);
int sort_insert(node **head,node* node);
int print(node *head);
int find_huffman_Code(char string[]);
node *del_head(node **head);
void paren(node *tree);
int store(node* head,char **A);
int findCodes(node *head,char c[],int j,int *byte_num);
int print_Code_Length(char string[]);
node *Find_huffman_Code(char string[]);

int main()
{ 
	char string[1000],ch;
	scanf("%[^\n]s",string);
	print_Code_Length(string);
	
}

int print_Code_Length(char string[])
{
	int j=0,byte_num=0;
	char c[100];
	node *head=Find_huffman_Code(string);
	findCodes(head,c,j,&byte_num);
	printf ("%d\n",byte_num);
}	

node *Find_huffman_Code(char string[])
{
	char ch;
	int len=0,num_nodes=0,n;
	char c[100],a;
	int j=0,byte_num=0,b=0;
	node *head=NULL;
	node *min1=NULL;
	node *min2=NULL;
	int freq[26]={0};
	while(string[len]!='\0')
	{
		ch=string[len];
		freq[ch-'a']+=1;
		len++;
	}
	for(int i=0;i<26;i++)
	{
		if(freq[i]!=0)
		{
			head=create(head,i+'a',freq[i]);
			num_nodes+=1;
		}
	}
	char A[num_nodes];
	node *p=head;
	int i=0;
	while(p!=NULL)
	{
		//printf("p->key=%c\n",p->key);
		A[i]=p->key;
		i++;
		p=p->next;
	}
																
	/*for(int i=0;i<num_nodes;i++)
		printf("%c\n",A[i]);*/
	//printf("Linked list after node insertion\n");
	//print(head);
	//printf("Linked list after sorting\n");
	Sort(&head);
	//print(head);
	n=num_nodes;
	while(n>1)
	{
		min1=del_head(&head);
		min2=del_head(&head);
		n=n-2;
		node *sumNode=getNode(' ',min1->freq+min2->freq);
		sumNode->left=min1;
		sumNode->right=min2;
		sort_insert(&head,sumNode);
		n=n+1;
	}
	//printf("After the formation\n");
	//print(head);
	//paren(head);
	return head;
	
}	

int findIndex(char s,char A[],int len)
{
	for(int i=0;i<len;i++)
	{
		if(A[i]==s)
			return i;
	}
}


int findCodes(node *head,char c[],int j,int *byte_num)
{
	//if(*found==1)
		//return c;
	//printf("----------------------------------entering findCodes-------------\n");
		
	if(head->left!=NULL)
	{
		c[j]='1';
		findCodes(head->left,c,j+1,byte_num);
	}
	if(head->right!=NULL)
	{
		c[j]='0';
		findCodes(head->right,c,j+1,byte_num);
	}
	if(head->left==NULL && head->right==NULL)
	{
		*byte_num+=(j*(head->freq));
		
	}

}


node *del_head(node **head)
{
	if(*head==NULL)
		return NULL;
	else
	{
		node *del_node=*head;
		*head=del_node->next;
		del_node->next=NULL;
		return del_node;
	}
}

node *getNode(char key,int freq)
{
	node *newNode=(node*)malloc(sizeof(node));
	newNode->key=key;
	newNode->freq=freq;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->next=NULL;
	return newNode;
}

node* create(node* head,char value,int freq)
{
        node *temp=getNode(value,freq);
        node *p=NULL;
        if(head==NULL)
        {
                head=temp;
        }
        else
        {
                p=head;
                while(p->next!=NULL)
                        p=p->next;
                //temp->prev=p;
                p->next=temp;
        }


        return head;
}


int Sort(node **head)
{
	node *p=NULL;
	node *current=NULL;
	current=*head;
	while(current!=NULL)
	{
		node *next=current->next;
		sort_insert(&p,current);
		current=next;
	}
	*head=p;
}

int sort_insert(node** head_ref, node* new_node) 
{ 
	node* current; 
	if (*head_ref == NULL || (*head_ref)->freq >= new_node->freq) 
	{ 
		new_node->next = *head_ref; 
		*head_ref = new_node; 
	} 
	else
	{ 
		current = *head_ref; 
		while (current->next!=NULL && current->next->freq < new_node->freq) 
		{ 
			current = current->next; 
		} 
		new_node->next = current->next; 
		current->next = new_node; 
	} 
}

int print(node* head)
{
	//printf("\nEntered print function\n");
	node *p=NULL;
	if(head==NULL)
		printf("No linked list");
	else
	{
		p=head;
		while(p!=NULL)
		{
			printf("%d ",p->freq);
			p=p->next;
		}
	}
	printf("\n");
}





void paren(node *tree)
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
