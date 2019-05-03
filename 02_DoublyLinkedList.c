#include <stdio.h>
#include<stdlib.h>

struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
} Node;

struct list{		
	struct Node* head;
	struct Node* tail;	
} list;


void init(struct  list* l,int value)
{
	struct Node* tmp;
	tmp = (struct Node*)malloc(sizeof(struct Node));
	tmp->value=value;
	tmp->next=NULL;
	tmp->prev=NULL;
	l->head = tmp;
	l->tail = tmp;
}

int clear(struct list* l)
{
    while(l->head!=NULL)
    {
    	struct Node *tmp=l->head;
        l->head=l->head->next;
        free(tmp);
    }
	l->head = NULL;
	l->tail = NULL;
}

int isEmpty(struct list* l)
{
	return l->head==NULL && l->tail==NULL;
}

struct Node* find(struct list* l,int k)
{
	struct Node *tmp=l->head;
	while(tmp->value!=k){
		if(tmp->next!=NULL){
			tmp=tmp->next;
		}else{
			return 0;
		}
	}
	return tmp;
}

struct Node* find_invers(struct list* l,int k)
{
	struct Node *tmp=l->tail;
	while(tmp->value!=k){
		if(tmp->prev!=NULL){
			tmp=tmp->prev;
		}else{
			return 0;
		}
	}
	return tmp;
}

int push_back(struct list* l, int x)
{
	if(isEmpty(l)==1)
		init (l,x);
	else
	{
		struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->value=x;
		tmp->prev=l->tail;
		tmp->next=NULL;
		l->tail=tmp;
		tmp->prev->next=tmp;
	}
	return 0;
}

int push_front(struct list* l,int x) 
{
	if(isEmpty(l)==1)
		init (l,x);
	else
	{
		struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->value=x;
		tmp->prev=NULL;
		tmp->next=l->head;
		l->head=tmp;
		tmp->next->prev=tmp;
	}
	return 0;
}

int insertAfter	(struct list* l,int num, int data)
{
	struct Node* tmp = l->head;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return 1;
	}
	struct Node *temp = malloc(sizeof(Node));
	temp->value=data;
	temp->next=tmp->next;
	temp->prev=tmp;
	tmp->next->prev=temp;
	tmp->next=temp;  
	return 0;   
}

int insertBefore(struct list* l,int num, int data)
{
	struct Node* tmp = l->head;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return 1;
	}
	struct Node *temp = malloc(sizeof(Node));
	temp->value=data;
	temp->prev=tmp->prev;
	temp->next=tmp;
	tmp->prev=temp;
	temp->prev->next=temp;      
	return 0; 
}

int removeFirst(struct list* l, int x)
{
	struct Node *findNode = find(l, x);
	if (findNode != NULL)
	{
		if (findNode==l->head && findNode==l->tail) {
			clear(l);
			return 0;
		}
		if (findNode==l->head)
		{
			l->head=findNode->next;
			findNode->next->prev=NULL;
		}
		else if(findNode==l->tail)
		{
			l->tail=findNode->prev;
			findNode->prev->next=NULL;
		}
		else if (findNode!=l->head && findNode!=l->tail)
		{
			findNode->next->prev=findNode->prev;
			findNode->prev->next=findNode->next;
		}
		free(findNode);
		return 0;
	}
	return -1;
}

int removeLast(struct list* l,int x)
{
	struct Node *findNode = find_invers(l, x);
	if (findNode != NULL)
	{
		if (findNode==l->head && findNode==l->tail) {
			clear(l);
			return 0;
		}
		if (findNode==l->head)
		{
			l->head=findNode->next;
			findNode->next->prev=NULL;
		}
		else if(findNode==l->tail)
		{
			l->tail=findNode->prev;
			findNode->prev->next=NULL;
		}
		else if (findNode!=l->head && findNode!=l->tail)
		{
			findNode->next->prev=findNode->prev;
			findNode->prev->next=findNode->next;
		}
		free(findNode);
		return 0;
	}
	return -1;
}

void print(struct list* l)
{
	struct Node* tmp=l->head;
	while(tmp->next!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}

void print_invers(struct list* l)
{
	struct Node* tmp=l->tail;
	while(tmp->prev!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->prev;
	}
	printf("%d\n", tmp->value);	
}



int main()
{
	int N,n,i;
	struct list* l=(struct list*)malloc(sizeof(struct list));	
	scanf("%d",&N);
	for (i=0;i<N;i++)
	{
		scanf("%d",&n);
		push_back(l,n);
	}
	print(l);
	
	for(int i=0;i<3;i++){
		scanf("%d",&n);
		if(find(l,n)!=NULL)
			printf("1");
		else
			printf("0");
	}
	printf("\n");

	scanf("%d",&n);
	push_back(l,n);
	print_invers(l);

	scanf("%d",&n);
	push_front(l,n);
	print(l);

	scanf("%d%d",&i,&n);
	insertAfter(l,i,n);
	print_invers(l);

	scanf("%d%d",&i,&n);
	insertBefore(l,i,n);
	print(l);

	scanf("%d",&n);
	removeFirst(l,n);
	print_invers(l);
	
	scanf("%d",&n);
	removeLast(l,n);
	print(l);

	clear(l);
	return 0;
}
