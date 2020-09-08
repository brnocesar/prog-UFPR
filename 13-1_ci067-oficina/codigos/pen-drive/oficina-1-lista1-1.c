#include <stdio.h>

int main(){
	int i = 25;
	short int s = 10;
	long int I = 50L;
	float f = 0.5;
	double d = 1.7;
	
	printf("1. f + s * i - 1 = %f\n", f + s * i - 1);
	printf("2. i / f + s * d = %F\n", i / f + s * d);
	printf("i / s * f = %f\n", i / s * f);
	printf("(double) i / s * f = %F\n", (double) i / s * f);
	printf("I / i + (int) d / f = %d\n\n", I / i + (int)( d / f));
	
	return 0;
}