#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int ordena_numeros(int vetor[], int tam){
	int aux, m, j, i;
	
	for(i=0; i<tam; i++){
		m=i; //posicao que o menor elemento deve ocupar, indice
		for(j=i+1; j<tam; j++){ /*indice j comeca com i+1 pois nao faz sentido comparar um elemento com ele mesmo*/
			if(vetor[j] <= vetor[m]) m = j;
		}//acha o indice do menor elemento
		/*troca o menor elemento pelo que esta na casa*/
		aux = vetor[i];
		vetor[i] = vetor[m];
		vetor[m] = aux;
	}
	
	return tam;
}

int main(){
	char string[N];
	int numeros[N], i, lim;
	
	printf("digite uma string: ");
	fgets(string, N-2, stdin);
	
	i = 0;
	while(string[i] != '\n'){
		numeros[i] = string[i];
		printf(" %d\n", numeros[i]);
		i++;
	}
	
	lim = ordena_numeros(numeros, i);
	
	for(i=0; i<lim; i++) printf("  %d\n", numeros[i]); /*teste*/
	
	return 0;
}