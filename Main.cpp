#include <iostream>
#include <fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
static int count=0;
struct btree
{
	int n;
	long int *line;
	long int *key;
	struct btree** child;
	int leaf;
};

struct btree* root=NULL;
struct btree* s;
int m,flag,sflag;

struct btree *findchild(long int key,struct btree *ptr)
{
	int i=0;
	while(key >= ptr->child[i]->key[0])
	{
		i++;
	}
	return ptr->child[i];
}

void splitchild(int c,struct btree* T,struct btree* s,long int k,long int line)//split child
{
	if(c==111)
		printf("\nsplit root");
	else
	printf("\nsplit child");

     printf("\n");

	struct btree* z=(struct btree*)malloc(sizeof(struct btree));
	z->key=(long int*)malloc((m-1)*sizeof(long int));
	z->line=(long int*)malloc((m-1)*sizeof(long int));
	z->child=(struct btree**)malloc(m*sizeof(struct btree));
	long int temp[m];
	long int temp2[m];
	int j;
	
	struct btree* x;
	x=T;
	
	for(j=0;j<m-1;j++)
	{
		temp[j]=T->key[j];
		temp2[j]=T->line[j];
	}
	
	j=m-2;
	while(j>=0 && temp[j]>k)
	{
		temp[j+1]=temp[j];
		temp2[j+1]=temp2[j];
		j--;
	}
    temp[j+1]=k;
    temp2[j+1]=line;
//	for(j=0;j<m;j++)
//		printf("\ttemp%d=%ld",j,temp[j]);
	
	if(sflag== 1)
	{
		for(j=0;j<(m/2);j++)
	    {
	      z->key[j] = temp[j+((m/2)+1)];
	      z->line[j]=temp2[j+(m/2)+1];
	      z->child[j+1] = findchild(temp[j+((m/2)+1)],x);
	    }

	    z->child[0] = findchild(temp[m/2],x);
	}
   
  	for(j=0;j<m/2;j++)
	{
		T->key[j]=temp[j];
		T->line[j]=temp2[j];
	}
	
	
	for(j=0;j<m/2;j++)
	{
		z->key[j]=temp[j+(m/2)+1];
		z->line[j]=temp2[j+(m/2)+1];
	}
  	
	j=s->n-1;
	
	while(j>=0 && s->key[j]>temp[m/2])
	{
		s->key[j+1]=s->key[j];
		s->line[j+1]=s->line[j];
		s->child[j+2] = s->child[j+1];
		j--;
	}
	s->key[j+1]=temp[m/2];
	s->line[j+1]=temp2[m/2];
	printf("\nroot->[%d]=%ld",j+1,s->key[j+1]);
	
	z->n=m/2;	
	T->n=m/2;
	s->child[j+1]=T;
	s->child[j+2]=z;
	s->n=s->n+1;
	s->leaf=0;

	if(sflag == 1)
    {
    	 z->leaf = 0;	
    }
    else
    {
    	 z->leaf = 1;
    }

}

void insertnonfull(struct btree* T,long int k,long int line)//insert in nonfull node
{
	int i=T->n-1;
	if(T->leaf==1)
	{
		printf("\ninsertion in leaf node\n");
		while(i>=0 && T->key[i]>k)
		{
			T->key[i+1]=T->key[i];
			T->line[i+1]=T->line[i];
			i--;
		}
		T->key[i+1]=k;
		T->line[i+1]=line;
		T->n=T->n+1;
	}
	else
	{
		 while(i>=0 && T->key[i]>k)
		 {
			 i--;
		 }
		
			 if(T->child[i+1]->n==m-1)
			 {
				 splitchild(i+1,T->child[i+1],T,k,line);
			 }
			 else
			 {
				insertnonfull(T->child[i+1],k,line);				
			 }
		 }
		
}

struct btree* insert(struct btree* ptr,long int k,long int line)//insert
{
	int j;
	if(ptr==NULL)
	{
		ptr=(struct btree*)malloc(sizeof(struct btree));
		ptr->key=(long int*)malloc((m-1)*sizeof(long int));
		ptr->line=(long int*)malloc((m-1)*sizeof(long int));
		ptr->child=(struct btree**)malloc(m*sizeof(struct btree));
		ptr->leaf=1;
		ptr->key[0]=k;
		ptr->line[0]=line;
		ptr->n=1;
		return ptr;
	}
    else if(ptr->n==m-1 )
		{
			if(root->leaf==1)
			{
				     s=(struct btree*)malloc(sizeof(struct btree));
					s->child=(struct btree**)malloc(m*sizeof(struct btree));
					s->key=(long int*)malloc((m-1)*sizeof(long int));
					s->line=(long int*)malloc((m-1)*sizeof(long int));
					s->n=0;
					s->child[0]=ptr;
					splitchild(0,ptr,s,k,line);
					ptr=s;
					return ptr;
			}
			else
			{
					printf("\n\nroot is full but child is not");
		               insertnonfull(ptr,k,line);
				  if(ptr->n==m)
				  {
				 	count++;
				 	printf("count = %d",count);
					printf("\n\nroot is full split it \n");
					sflag=1;
					s=(struct btree*)malloc(sizeof(struct btree));
					s->child=(struct btree**)malloc(m*sizeof(struct btree));
					s->key=(long int*)malloc((m-1)*sizeof(long int));
					s->line=(long int*)malloc((m-1)*sizeof(long int));
					s->n=0;
					s->child[0]=ptr;
					splitchild(111,ptr,s,ptr->key[ptr->n-1],ptr->line[ptr->n-1]);
					ptr=s;
					return ptr;
				  }	
		}
	}
		else
		{
			insertnonfull(ptr,k,line);
		}
		return ptr;
	
}
	
void inorder(struct btree *ptr)//inorder
{
	int i;
	for(i = 0; i < ptr->n; i++)
	{
		if(ptr->leaf == 0)
			inorder(ptr->child[i]);

		printf("%ld,",ptr->key[i]);
	}

	if(ptr->leaf == 0)
		inorder(ptr->child[i]);
}
					

void search(struct btree *ptr,long int num) // Search function
{
	int i;
	string div;
  	string sr;
  	string gr_no;
  	string name;
  	string gender;
  	string branch;
	for(i = 0; i < ptr->n; i++)
	{
		if(ptr->leaf == 0)
			search(ptr->child[i],num);

		if(ptr->key[i] == num)
		{	
			printf("\nNumber found in tree= %ld\n",ptr->key[i]);
			printf("Byte no. =%ld\n",ptr->line[i]);
			flag = 1;
			
			ifstream il("test2.csv");
			il.seekg(ptr->line[i],ios::beg);
			
			getline(il,div,',');
    			getline(il,sr,',');
    			getline(il,gr_no,',');
    			getline(il,name,',');
    			getline(il,gender,',');
    			getline(il,branch,'\n');
			
			std::cout << "Name: "<<name<<'\n';
    			std::cout << "Gr_no: "<<gr_no<<'\n';
    			std::cout << "Branch: "<<branch<<'\n';
    			std::cout << "sr: "<<sr<<'\n';
    			std::cout << "div: "<<div<<'\n';
		}
	}

	if(ptr->leaf == 0)
	{
		search(ptr->child[i],num);
	}
	
}


int main()
{
  ifstream ip("test2.csv");
  m=40;
  flag=0;
  sflag=0;
  
  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string div;
  string sr;
  string gr_no;
  string name;
  string gender;
  string branch;
  long int no=0;
  int i,l,count=0;
  while(ip.good())
  { 
    getline(ip,div,',');
    getline(ip,sr,',');
    getline(ip,gr_no,',');
    getline(ip,name,',');
    getline(ip,gender,',');
    getline(ip,branch,'\n');
    no =(long int)gr_no[0]-48;
    
    for(i=1;i<=gr_no.length()-1;i++)
    {
    	   no = no*10 + ((long int)gr_no[i]-48);
//    	   printf("no=%ld",no);
    }
    
    root=insert(root,no,count);
    count = count + div.length() + sr.length() + gr_no.length() + name.length() + gender.length() + branch.length() + 6;
    cout << "Name: "<<name<<'\n';
    cout << "Gr_no: "<<gr_no<<'\n';
    cout << "Branch: "<<branch<<'\n';
    cout << "sr: "<<sr<<'\n';
    cout << "div: "<<div<<'\n';
    
    cout << "-------------------" << '\n';
  }
  
  do
  {
	  cout<<"ENter gr_no.";
	  cin>>no;
	  search(root,no);
 	  if(flag!=1)
 	  {
  		cout<<"Entry not found";
	  }
  	  cout<<"Continue?\n";
  	  cin>>l;
  }while(l!=0);
  ip.close();
  
  return 0;
}
