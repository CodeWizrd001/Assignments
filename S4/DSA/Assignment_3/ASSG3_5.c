#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hashNODE
{

	int data;

	int deleted;

	int occupied; 

	struct hashNODE* link;
};

int m,m2;
int c1,c2;

struct hashNODE* hashARR = NULL;
// create a hash table
void hashTable(struct hashNODE **myArray)
{
	     *myArray = malloc(m * sizeof **myArray);
}


// linear probing
int linear();
int insertl();
int searchl();
int deletel();
int print();

//quadratic probing
int quadratic();
int insertq();
int searchq();
int deleteq();

//double hashing
int doubleh();
int insertd();
int searchd();
int deleted();


int main()
{

	char flag;
	scanf("%s",&flag);

	switch(flag)
	{
		case 'a': linear(); break;
		case 'b': quadratic(); break;
		case 'c': doubleh(); break;
		default: return 0;
	}
	return 0;
}

//double hashing part
int doubleh()
{
	int i;
	scanf("%d",&m);
	hashTable(&hashARR);
	for(i=0;i<m;i++){
		hashARR[i].occupied = 0;
		hashARR[i].deleted = 0;
	}
	char op;
	do 
	{
		scanf("%s",&op);
		switch(op)
		{

			case 'i': insertd(); break;
			case 's': searchd(); break;
			case 'd': deleted(); break;
			case 'p': print();break;
			default: return 0;
		}
	} while(op!='T');
}

//inserting using double hashing
int insertd()
{
	int data,key,flag=0;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int i,j;
	for(i=m-1;i>1;i--)
	{
		for(j = 2; j <= i/2; ++j)
		{
			if(i % j == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{m2=i; break;}
		flag=0;			//m2 is prime number just less than the table size ie m
	}
	int keyM2=m2-data%m2;	
	i=0;
	while(hashARR[key].occupied==1&&i<m)
	{
		key= (keyM+i*keyM2)%m;
		i++;
	}
	hashARR[key].data=data;
	hashARR[key].occupied=1;
	hashARR[key].deleted=0;
}

// double hashing search
int searchd()
{
	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int keyM2=m2-data%m2;//equating hashes

	int i=0;

	while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
	{
			key= (keyM+i*keyM2)%m;
				i++;
					if(i==m) break;
	}

	if(hashARR[key].data==data) {printf("1\n"); return 1;}
	else {printf("-1\n"); return -1;}
}

// double hashing deleting
int deleted()
{

	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int keyM2=m2-data%m2;
	int i=0;

	while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
	{
			key= (keyM+i*keyM2)%m;
				i++;
					if(i==m) break;
	}

	if(hashARR[key].data==data)
	{
			hashARR[key].data=0;
			hashARR[key].occupied=0;
			hashARR[key].deleted=1;
	}
	else return 0; 
}

// duadratic probing
int quadratic()
{
	int i;	
	scanf("%d",&m);
	hashTable(&hashARR);
	for(i=0;i<m;i++){
		hashARR[i].occupied = 0;
		hashARR[i].deleted = 0;
	}
	scanf("%d",&c1);
	scanf("%d",&c2);
	char op;
	do 
	{
		scanf("%s",&op);
		switch(op)
		{
			case 'i': insertq(); break;
			case 's': searchq(); break;
			case 'd': deleteq(); break;
			case 'p': print();break;
			default: return 0;
		}
	} while(op!='t');
}

//quadratic probing  inserting
int insertq()
{
	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int i=0;
	while(hashARR[key].occupied==1&&i<m)
	{       i++;
		key= (keyM+i*c1+i*i*c2)%m;
	}
	hashARR[key].data=data;
	hashARR[key].occupied=1;
	hashARR[key].deleted=0;
}
//quadratic probing searchig
int searchq()
{
	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int i=0;
	while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
	{
			key= (keyM+i*c1+i*i*c2)%m;
			i++;
			if(i==m) 
				break;
	}
	if(hashARR[key].data==data) {printf("1\n"); return 1;}
	else {printf("-1\n"); return -1;}
}

//deleteing quadratic probing
int deleteq()
{

	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;

	int i=0;

	while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
	{
			key= (keyM+i*c1+i*i*c2)%m;
			i++;
			if(i==m) break;
	}

	if(hashARR[key].data==data)
	{

		hashARR[key].data=0;
		hashARR[key].occupied=0;
		hashARR[key].deleted=1;
	}
	else 
		return 0; 
}

// linear probing
int linear()
{
	int i;
	scanf("%d",&m);
	hashTable(&hashARR);
	for(i=0;i<m;i++){
		hashARR[i].occupied = 0;
		hashARR[i].deleted = 0;
	}
	char op;
	do 
	{
		scanf("%s",&op);
		switch(op)
		{
			case 'i': insertl(); break;
			case 's': searchl(); break;
			case 'd': deletel(); break;
			case 'p': print();break;
			default: return 0;
		}
		
	} while(op!='T');
}
//linear inserting
int insertl()
{
	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int i=0;
	while(hashARR[key].occupied==1)
	{
			key= (keyM+i)%m;
				i++;
	}
	hashARR[key].data=data;
	hashARR[key].occupied=1;
	hashARR[key].deleted=0;
}
int searchl()
{
	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int i=0;
	while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
	{
		key= (keyM+i)%m;
		i++;
	}
	if(hashARR[key].data==data) {printf("1\n"); return 1;}
	else {printf("-1\n"); return -1;}
}
int deletel()
{
	int data,key;
	scanf("%d",&data);
	int keyM = data%m;
	key = keyM;
	int i=0;
	while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
	{
		key= (keyM+i)%m;
		i++;
	}
	if(hashARR[key].data==data)
	{
		hashARR[key].data=0;
		hashARR[key].occupied=0;
		hashARR[key].deleted=1;
	}
	else 
		return 0; 
}
int print()
{
	int i;
	for(i=0;i<m;i++)
	{
			if(hashARR[i].occupied==0)
			{
			       	printf("%d ()\n",i);
			}
			else 
				printf("%d (%d)\n", i, hashARR[i].data);
	}
}
