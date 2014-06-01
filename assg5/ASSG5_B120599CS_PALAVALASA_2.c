#include<stdio.h>
#include<stdlib.h>

int time;
int read(FILE *p)
{
	int k;
	fscanf(p,"%d",&k);
	return k;
}
void dfsv(int **a,int u,int ver,int *d,int *color,int *f,int *pi)
{
	time = time +1;
	*(d+u) = time;
	*(color+u) = 1;
	int v;
	for(v=0;v<ver;v++)
	{
		if(*(*(a+v)+u) == 1)
		{
//			printf("%d and %d are connected\n",u,v);
			if(*(color+v) == 0)
			{
				*(pi+v) = u;
				printf("%d ",v);
				dfsv(a,v,ver,d,color,f,pi);
			//	printf("%d ",v);
			}
		}
	}
//	printf("%d ",u);
	*(color+u) = 2;
	time = time + 1;
	*(f+u) = time;
	
}
void dfs(int **a,int ver,int start)
{
	int *color;
	color = malloc(ver*sizeof(int));
	int *pi;
	pi  = malloc(ver*sizeof(int));
	int *d;
	d = malloc(ver*sizeof(int));
	int *f;
	f = malloc(ver*sizeof(int));
	int u;
	for(u=0;u<ver;u++)
	{
		*(color+u) = 0;
		*(pi+u) = -1;
	}
	time = 0;
	printf("%d ",start);
	for(u=0;u<ver;u++)
	{
		int k = (start+u)%ver;
		if(*(color+k) == 0)
		dfsv(a,k,ver,d,color,f,pi);
		
	}

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
		int cost = read(p);
                *(*(adj + one)+two) = 1;
                *(*(adj + two)+one) = 1;
                --edg;
        }
        return adj;

}

void main()
{
        char *b;
        b = malloc(30*sizeof(char));
        printf("enter the file name: ");
        scanf("%s",b);
        FILE *p;
        p = fopen(b,"r+");
//      if(p == NULL)
//      printf("go goa gone\n");
        int ver = read(p);
        int ed = read(p);
//      printf("%d ",ver);
//      printf("%d ",ed);
        int **a;
        a = make(ver,ed,p);
        int start;
        printf("start from: ");
        scanf("%d",&start);
        dfs(a,ver,start);
}
