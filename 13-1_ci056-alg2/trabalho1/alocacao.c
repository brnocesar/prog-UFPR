#include<stdio.h>
#include<stdlib.h>

struct lista{
	int x;
	int *v;
};

typedef struct lista lista;

void main()
{
	lista* l;
	l=(lista*)malloc(3*sizeof(lista));	
	l[0].v=(int*)malloc(4*sizeof(int));
	l[1].v=(int*)malloc(4*sizeof(int));
	l[1].v=(int*)realloc(l[1].v,5*sizeof(int));
	l[0].x=5;
	l[0].v[0]=0;
	l[0].v[1]=1;
	l[0].v[2]=2;
	l[1].x=6;
	l[1].v[0]=10;
	l[1].v[1]=11;
	l[1].v[2]=12;
	printf("%d %d %d %d\n",l[0].x,l[0].v[0],l[0].v[1],l[0].v[2]);
	printf("%d %d %d %d\n",l[1].x,l[1].v[0],l[1].v[1],l[1].v[2]);
	free(l);
}
