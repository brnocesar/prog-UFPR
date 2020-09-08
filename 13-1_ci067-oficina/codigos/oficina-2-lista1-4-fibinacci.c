#include <stdio.h>
#define N 20

int main(){
	int i, vet[N];
	
	vet[0]=0; vet[1]=1;
	for(i=2; i<N; i++){
		vet[i] = vet[i-1] + vet[i-2];
	}
	
	printf(" |");
	for(i=0; i<N; i++){
		printf(" %d |", vet[i]);
	}
	printf("\n");
	
	return 0;
}