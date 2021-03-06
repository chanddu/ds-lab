#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *parent;
};
typedef struct node element;
typedef element *link;

int read(FILE *p)
{
	int k;
	fscanf(p,"%d",&k);
	return k;
}

void make_set(link a,int d)
{
	a->parent = a;
	a->data = d;
}

link find_set(link a)
{
//	if(a != NULL)
//	printf("not gone\n");
	while(a->parent != a)
	a = a->parent;
	return a;
}

void unio(link x,link y)
{
	link rootx = find_set(x);
	link rooty = find_set(y);
	rootx->parent = rooty;
}

link search(link a,int max,int dat)
{
	int i=0;
	for(i=0;i<max;i++)
	{
		if((a+i)->data == dat)
		return (a+i);
	}
	return NULL;
}
void do_it(FILE *p)
{
	int mode = read(p);
	link arr = malloc(30*sizeof(element));
	int offset = 0;
	while(mode)
	{
		if(mode == 1)
		{
			int dat = read(p);
			make_set((arr+offset),dat);
			offset++;
			printf("\n");
		}
		if(mode == 2)
		{
			int dat = read(p);
			link hell = search(arr,offset,dat);
			link set = find_set(hell);
			printf("%d\n",(set->data));
		}
		if(mode == 3)
		{
			int dat1 = read(p);
			int dat2 = read(p);
			link d1 = search(arr,offset,dat1);
			link d2 = search(arr,offset,dat2);
			unio(d1,d2);
			printf("\n");	
		}
		mode = read(p);
	}
}
void main()
{
	char *a;
	a = malloc(30*sizeof(char));
	printf("enter file name: ");
	scanf("%s",a);
	FILE *p;
	p = fopen(a,"r+");
	do_it(p);
}
