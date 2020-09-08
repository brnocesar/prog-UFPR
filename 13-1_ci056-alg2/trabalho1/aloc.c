#include<stdio.h>
#include<stdlib.h>

struct estr{
	int *x;
};

typedef struct estr estr;

void main()
{
	estr* l;
	l=(estr*)malloc(3*sizeof(estr));
	l[0].x=(int*)malloc(5*sizeof(int));
	l[1].x=(int*)malloc(5*sizeof(int));
	l=(estr*)realloc(l,4*sizeof(estr));
	l[0].x=(int*)realloc(l[0].x,2*sizeof(int));
	l[1].x=(int*)realloc(l[1].x,2*sizeof(int));
	l[0].x[0]=0;
	l[0].x[1]=1;
	l[1].x[0]=10;
	l[1].x[1]=11;
	printf("%d %d %d %d\n",l[0].x[0],l[0].x[1],l[1].x[0],l[1].x[1]);
}
