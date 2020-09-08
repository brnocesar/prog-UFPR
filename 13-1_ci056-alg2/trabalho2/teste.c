#include <stdio.h>

int main(){
	int vetor[4];
	vetor[0] = 'a';
	vetor[1] = 6;
	vetor[2] = 'H';
	vetor[3] = 39;
	
	int i;
	for(i=0; i<4; i++){
		printf("(int) (int) %d\n", vetor[i]);
	}
	for(i=0; i<4; i++){
		printf("(char) (int) %c\n", vetor[i]);
	}
	
	char vet[4];
	vet[0] = 'a';
	vet[1] = 6;
	vet[2] = 'H';
	vet[3] = 39;
	for(i=0; i<4; i++){
		printf("(int) (char) %d\n", vet[i]);
	}
	for(i=0; i<4; i++){
		printf("(char) (char) %c\n", vet[i]);
	}
}