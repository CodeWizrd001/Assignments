#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct node
{
	char word[100];
	struct node *next;
} Node;

void insert(Node **head,char s[])
{
	    Node *temp,*new_node;
	    temp=*head;
	    if(temp==NULL)
	    {
		    *head=(Node*)malloc(sizeof(Node));
		    strcpy((*head)->word,s);
		    (*head)->next=NULL;
	    }
	    else
	    {

	            while(temp->next!=NULL)
	            {
		            if(!strcmp(s,temp->word))
			            return ;
		            temp=temp->next;
		    }
		    if(!strcmp(s,temp->word))
			    return ;
		    new_node=(Node*)malloc(sizeof(Node));
		    strcpy(new_node->word,s);
		    new_node->next=NULL;
		    temp->next=new_node;
		    temp=new_node;
	    }
}
int hashfun(char Word[],int capacity)
{
	    return strlen(Word)%capacity;
}
void hashing(char s[],int n)
{
	 Node b[10000];
         int m=0,k=0,l,count=0;
         int i=0;
         while(s[i]!='\0')
         {
 	        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		        b[m].word[k++]=s[i];
	        else if(s[i]==' ')
		{
			count++;
			m++;
			k=0;
		}
	        i++;
         }
         int index,co;
         Node *a[n];
         Node *temp;
         temp=(Node*)malloc(sizeof(Node));
         for(i=0;i<n;i++) a[i]=NULL;
	 for(i=0;i<=m;i++)
	 {
	      index=hashfun(b[i].word,n);
	      insert(&a[index],b[i].word);
	 }
         for(i=0;i<n;i++)
         {
              if(a[i]==NULL)
              printf("NULL\n");
              else
	      {
	 	     printf("%s",a[i]->word);
		     a[i]=a[i]->next;
		     while(a[i]!=NULL)
		     {
			     printf(" %s",a[i]->word);
			     a[i]=a[i]->next;
		     }
		     printf("\n");
	      }
          }
}
int main()
{
	int n;
	scanf("%d",&n);
	char s[1000000];
	scanf("\n");
	scanf("%[^\n]s",s);
	hashing(s,n);
}

