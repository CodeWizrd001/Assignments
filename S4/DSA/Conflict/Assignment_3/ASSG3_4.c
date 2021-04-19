#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int hashcode(char x)
{
	return x-'a';
}

int checker(char*a,int *T,int *N,int x) 
{ 
	int hs ;
	for(int i=0;i<x;i+=1)
	{
		hs = hashcode(a[i]) ;
		
		if(hs<0)
			hs += 32 ;
		if(T[hs]!=N[hs])	
			return 0 ;
	}
	return 1 ;
}


void permut(char pat[], char str[])
{
	int l,m,i,hash,rhash,phash=0,shash=0,flag=0;
	
	l=strlen(pat);
	m=strlen(str);
	
	pat[l-1]='\0';
	str[m-1]='\0';
	
	l--;
	m--;
	
	int *pTable;
	int *sTable;
	
	pTable=(int*)calloc(26,sizeof(int));
	sTable=(int*)calloc(26,sizeof(int));
	
	for(i=0;i<l;i++)
	{
		hash=hashcode(pat[i]);
		pTable[hash]+=1;
		phash+=hash;
	}

	for(i=0;i<m;i++)
	{
		
		if(flag)
			break;

		hash=hashcode(str[i]);
		sTable[hash]++;
		shash+=hash;
	
		rhash=0;
		if(i-l>=0)
		{
			rhash=hashcode(str[i-l]);
			sTable[rhash]--;	
		}
			
		shash-=rhash;
			
		if(shash==phash)
			if(checker(pat,pTable,sTable,l))
				flag=1;		
		
		
	}
	if(flag)
		printf("YES\n");
	else
		printf("NO\n");	
}


void main()
{
	char *str;
	char *pat;
	
	int t;
	scanf("%d",&t);
	
	while(t)
	{
		str=(char*)malloc(10000*sizeof(char));
		pat=(char*)malloc(1000*sizeof(char));
		
		scanf("\n");
		fgets(pat,1000,stdin);
		//scanf("\n");
		fgets(str,10000,stdin);

		//printf("%s:%s %ld \n",pat,str,strlen(pat));
		
		permut(pat,str);
		
		t--;
		
	}
}
