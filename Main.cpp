#include<iostream>
#include<stdlib.h>
#include<string>
#define MAX 20

using namespace std;
struct RBT
{
	int key;
	string str;
	int color;
	
	struct RBT *left;
	struct RBT *right;
	struct RBT *parent;
};

////////////

struct stack
{
	struct RBT *a[MAX];
 	int top;
 	int size;
}p;
struct stack *s=&p;

void push(struct stack *s,struct RBT *x)
{
	if(s->top == MAX -1)
	{
		cout<<" Stack overflow "<<endl;
	}
	else
	{ 
		s->top++;
		s->size++;
		s->a[s->top] = x;
	}
}

struct RBT *pop(struct stack *s)
{
	if(s->top == -1)
	{
		cout<<"Stack underflow"<<endl;
		return NULL ;
	}
	else
	{
		struct RBT *x = s->a[s->top];
		s->top--;
		s->size--;
		return x;
	}
}


////////////

struct Queue
{
	struct RBT *x[MAX];
	int front,rear,size;
}n;
struct Queue *q=&n;

void init_q()
{
	q->front=-1;
	q->rear=-1;
	q->size=0;
}

void init_s()
{
	s->top=-1;
	s->size=0;
}

void enq(struct RBT *x)
{
	if((q->rear + 1)%MAX == q->front && q->front==0)
	{
		cout<<"Q is full"<<endl;
	}
	else if(q->front == -1 && q->rear == -1)
		{
			q->front=0;
			q->rear=0;
			q->size++;
		     q->x[q->rear]=(struct RBT*)malloc(sizeof(struct RBT));
			q->x[q->rear] = x;
		}
	else
		{
			q->rear = (q->rear + 1)%MAX;
			q->x[q->rear]=(struct RBT*)malloc(sizeof(struct RBT));
			q->x[q->rear] = x;
			q->size++;
		}
}

struct RBT *deq()
{
	if(q->rear ==-1 && q->front==-1 )
	{	
		cout<<"Q is empty"<<endl;
		return NULL;
	}
	else if(q->front == q->rear)
	{
		struct RBT *x =(struct RBT*)malloc(sizeof(struct RBT));
  		x=q->x[q->front];
 		q->front=-1;
  	 	q->rear=-1;
		q->size=0;
		return x;  
	}
	else
	{
		struct RBT *x =(struct RBT*)malloc(sizeof(struct RBT));
		x=q->x[q->front];
		q->size--;
		q->front=(q->front+1)%MAX;
		return x;
	}
}

int size_q()
{
	return q->size;
}
int size_s()
{
	return s->size;
}

///////
class Treemap
{
	private:
	 int size ;
	public:
	struct RBT *root;
	Treemap()
	{
		root = NULL;
	}
	struct RBT *add(int x,string s);
	void insert(int x,string s);
	void right_rotate(struct RBT *T);
	void left_rotate(struct RBT *T);
	bool contains_key(int k);
	bool contains_value(string s);
	int sizeofmap();
	string get(int k);
	void headmap(int k);
	void firstkey();
	friend void inorder();	
};

void Treemap::firstkey()
{
	if(root == NULL)
	{
	cout<<"Tree empty\n";
	return;
	}
	struct RBT *p = root;
	while(p->left!=NULL)
		p = p->left;
	cout<<"\n key = "<<p->key;
}

void Treemap::headmap(int k)
{
	init_s();
	struct RBT *t=root;
	int flag=0;
	while(t!=NULL)
	{
	    push(s,t);
	    t=t->left;
	}
	while(size_s())
	{
	     t=pop(s);
	     if(t->key<k)
	    	{
	    		cout<<" "<<t->key<<" ";
	    		if(t->right!=NULL)
	    		{
	     	   t=t->right;
	     	   if(t->key<k)
	     	   {
	 		   	cout<<" "<<t->key<<" ";
	     	   	while(t->left!=NULL)
	    		   	{
	     	  		 push(s,t);
	     	  		 t=t->left;
	    		   	}
			   }
	    		}	
	     }
	}
}

string Treemap::get(int k)
{
	struct RBT *p;
	p = root;
	while(p!=NULL)
	{
		if(k == p->key)
		break;
		if(k < p->key)
			p = p->left;
		else
			p = p->right;
	
	}
	if(p == NULL)
		return "No such Key";
	else
		return p->str;
}

int Treemap::sizeofmap()
{
	return size;
}

bool Treemap::contains_key(int k)
{
	struct RBT *p;
	p = root;
	while(p!=NULL)
	{
		if(k == p->key)
		break;
		if(k < p->key)
			p = p->left;
		else
			p = p->right;
	
	}
	if(p == NULL)
		return false;
	else
		return true;

}

bool Treemap::contains_value(string s)
{
	if(root == NULL)
	return false;
	init_q();
	enq(root);
	struct RBT *p;
	int flag=0;
	while(size_q())
	{
		p = deq();
		if(s == p->str)
		{
			flag=1;
			break;	
		}
		if(p->left!=NULL)
		enq(p->left);
		if(p->right!=NULL)
		enq(p->right);
	
	}
	if(flag==1)
		return true;
	else
		return false;
	
}

void inorder(struct RBT *T)
{
	if(T!=NULL)
	{
		inorder(T->left);
		cout<<" "<<T->key;
//		cout<<" c ="<<T->color<<endl; 
		cout<<" value= "<<T->str<<endl;
		inorder(T->right);
	}

}

struct RBT *Treemap::add(int x,string s)
{
     struct RBT *p,*q;
	p = root;
	q = root;
	while(p!=NULL)
	{
		if(x > p->key)
		{
			q = p;
			p = p->right;
		}
		else
		{
			q = p;
			p = p->left;
		}
	}
	struct RBT *u = new RBT;
	u->key = x;
	u->left = NULL;
	u->right = NULL;
	u->color = 1;
	u->parent = q;
	u->str = s;
	
	if(root == NULL)
	return u;
	
	if(u->key > q->key)
	{
		q->right = u;
	}
	else
		q->left = u;
	cout<<"he1\n";
	return u;
}

void Treemap::right_rotate(struct RBT *T)
{
	struct RBT *temp;
	temp = T->parent->parent;
	T->parent->left = T->right;
	if(T->right!=NULL)
		T->right->parent = 	T->parent;
	T->right = T->parent;
	T->parent->parent = T;
	T->parent = temp;
	T->right->color = 1;
	T->color = 0;
	
	if(temp == NULL)
	{
		T->parent = NULL;
		root = T;
	}
	else if(T->right == temp->right)
	{
		temp->right = T;
	}
	else
	{
		temp->left = T;
	}

}

void Treemap::left_rotate(struct RBT *T)
{
	struct RBT *temp;
	temp = T->parent->parent;
	T->parent->right = T->left;
	if(T->left!=NULL)
		T->left->parent = 	T->parent;
	T->left = T->parent;
	T->parent->parent = T;
	T->parent = temp;
	T->left->color = 1;
	T->color = 0;
	if(temp == NULL)
	{
		T->parent = NULL;
		root = T;
	}
	else if(T->left == temp->right)
	{
		temp->right = T;
	}
	else
	{
		temp->left = T;
	}	

}


void Treemap::insert(int x,string s)
{
	
	struct RBT *u = add(x,s);
	if(root == NULL)
	{
		root = u;
		root->color = 0;
	}
	size++;
	while( u!=root && u->parent->color == 1)
	{
		if( u->parent == u->parent->parent->left)
		{
			if(u->parent->parent->right!=NULL)
			{
				if(u->parent->parent->right->color == 1) // LLr,LRr
				{
					u->parent->parent->right->color = 0;
					u->parent->color = 0;
			
					if(u->parent->parent!=root)
					{
						u->parent->parent->color = 1;
					}
					u = u->parent->parent;
				}
				else // LLb,LRb
				{	
					if(u == u->parent->left)
					{
						right_rotate(u->parent);
					}
					else
					{
						left_rotate(u);
						right_rotate(u);						
					}
				}
			}
			else // LLb,LRb
			{
				if(u == u->parent->left)
				{
//					
					right_rotate(u->parent);
				}
				else
				{
//			
					left_rotate(u);
			
					right_rotate(u);
					
				}
			}
		}
		else
		{
//		
			if(u->parent->parent->left!=NULL)
			{
//				
				if(u->parent->parent->left->color == 1) // RLr,RRr
				{
					u->parent->parent->left->color = 0;
					u->parent->color = 0;
					if(u->parent->parent!=root)
					{
						u->parent->parent->color = 1;
					}
					u = u->parent->parent;
				}	
				else // RLb,RRb
				{
					
					if(u == u->parent->right)
					{
						left_rotate(u->parent);
					}	
					else
					{
						right_rotate(u);
						left_rotate(u);
					}
				}
			}
			else // RLb,RRb
			{
//			
				if(u == u->parent->right)
				{
					left_rotate(u->parent);
				}	
				else
				{
					right_rotate(u);
					left_rotate(u);
				}
			}
		}
	}

}

 

int main()
{
	Treemap *t1 = new Treemap();
	int c;
	while(1)
	{
		cout<<"\n\nEnter your choice\n";
		cout<<"1.Insert \n2.Sizeofmap \n3.Contains key \n4.Contains Value\n5.Headmap \n6.Get value\n7.exit\n";
		cin>>c;
		int k;
		string v;
		switch(c)
		{
			case 1:
			cout<<"Enter key\n";
			cin>>k;
			cout<<"Enter Value\n";
			cin>>v;
			t1->insert(k,v);
			cout<<"Insertion successfull\n";	
			break;
			
			case 2:
			cout<<"Size of map is = "<<t1->sizeofmap();		
			break;
			
			case 3:
			cout<<"Enter key to check if its present\n";	
			cin>>k;
			cout<<t1->contains_key(k);				
			break;
			
			case 4:
			cout<<"Enter value to check if its present\n";	
			cin>>v;
			cout<<t1->contains_value(v);				
			break;
			
			
			case 5:
			cout<<"Enter key for Headmap\n";
			cin>>k;
			t1->headmap(k);
			break;
			
			case 6:
			cout<<"Enter key to get its value\n";
			cin>>k;
			cout<<"Value = "<<t1->get(k);			
			break;
			
			case 7:
			t1->firstkey();
			
			case 8:
			exit(0);
		}
	}
	
return 0;
}

