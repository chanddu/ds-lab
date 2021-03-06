#include<stdio.h>
#include<stdlib.h>

struct node
{
	struct node *prev;
	int key;
	struct node *next;
};

typedef struct node ELEMENT;
typedef ELEMENT *LINK;

LINK  head = NULL;
LINK tail = NULL;
int empty_que()
{
	return (head == NULL);
}
int read(FILE *p)
{
	int k;
	fscanf(p,"%d",&k);
	return k;
}
void enque(int ins)
{
	LINK temp;
	temp = tail;
	if (tail == NULL)
	{
		tail = malloc(sizeof(ELEMENT));
		tail->key = ins;
		tail->next = NULL;
		tail->prev = NULL;
		if(head == NULL)
		head = tail;
	}
	else
	{
		tail->prev = malloc(sizeof(ELEMENT));
		temp = tail->prev;
		temp->key = ins;
		temp->next = tail;
		temp->prev = NULL;
		tail = tail->prev;
	}
}
int deque()
{
	LINK temp = head;
	if(temp == NULL)
	printf("EMPTY\n");
	else
	{
		head = head->prev;
		if(head != NULL)
		head->next = NULL;
		else
		tail = NULL;
	}
	return (temp->key);
}
int** make(int ver,int edg,FILE *p)
{
	int **adj;
	adj = malloc(ver*sizeof(int *));
	int i;
	for(i=0;i<ver;i++)
	{
		*(adj+i) = malloc(ver*sizeof(int));
	}
	while(edg)
	{
		int one = read(p);
		int two = read(p);
		int make = read(p);
		*(*(adj + one)+two) = 1;
		*(*(adj + two)+one) = 1;
		--edg;
	}
	return adj;
	
}
void bfs(int **a,int ver,int s)
{
	int color[ver];
	int d[ver];
	int pi[ver];
	int i;
	for(i=0;i<ver;i++)
	{
		color[i] = 0;
		d[i] = -1;
		pi[i] = -1;
	}
	color[s] = 1;
	d[s] = 0;
	pi[s] = -1;
	enque(s);
	printf("%d ",s);
	while(empty_que() == 0)
	{
		int u = deque();
		int v;
		for(v = 0;v < ver;v++)
		{
			if(*(*(a+u)+v) == 1)
			{
//				printf("entering if 1\n");
				if(color[v] == 0)
				{
//					printf("entering if 2\n");
					printf("%d ",v);
					color[v] = 1;
					d[v] = d[u] + 1;
					pi[v] = u;
					enque(v);
				}
			color[u] = 2;
			}
		}
	}

}
void main()
{
	char *b;
	b = malloc(30*sizeof(char));
	printf("enter the file name: ");
	scanf("%s",b);
	FILE *p;
	p = fopen(b,"r+");
//	if(p == NULL)
//	printf("go goa gone\n");
	int ver = read(p);
	int ed = read(p);
//	printf("%d ",ver);
//	printf("%d ",ed);
	int **a;
	a = make(ver,ed,p);
	int start;
	printf("start from: ");
	scanf("%d",&start);
	bfs(a,ver,start);
}
