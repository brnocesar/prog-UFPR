#include <stdio.h>
#define N 10

void contafreq(int vetor[]){
	int copia[N], i, j, contador;
	
	for(i=0; i<N; i++) copia[i] = vetor[i]; // clona o vetor
	
	for(i=0; i<N; i++){
		contador = 0;
		for(j=0; j<N; j++){
			if(vetor[i] == copia[j]){
				copia[j] = -1;
				contador++;
			}
		}
		if(contador >= 2){
			printf(" %d ", vetor[i]);
			vetor[i] = -1;
		}
	}
	printf("\n");
}

int main(){
	int vetor[N], i;
	
	printf("digite %d inteiros positivos:\n", N); 
	for(i=0; i<N; i++) scanf("%d", &vetor[i]);
	
	contafreq(vetor);
	
	return 0;
}