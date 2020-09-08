#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100


void ordena(int vetor[], int tam){
	int aux, copia[N], i, j;

	for(i=0; i<tam; i++) copia[i] = vetor[i]; //faz uma copia do vetor


	for(i=0; i<tam; i++){
		aux = 0;
		for(j=0; j<tam; j++){
			if(copia[aux] > copia[j] && copia[aux] > vetor[i-1]) aux = j;
		}
		vetor[i] = copia[aux];
	}
}//incompleta

int main(){
	char string[N];
	int numeros[N], i, lim;

	printf("digite uma string: ");
	fgets(string, N, stdin);

	i = 0;
	while(string[i] != '\0'){
		if(string[i] == '\n') lim = i-1;
		numeros[i] = string[i];
		i++;
	} //determina ate que indice existem caracteres validos

	for(i=0; i <= lim; i++) printf("%d\n", numeros[i]); //imprime codigo ASCII dos caracteres
	/*funciona daqui pra cima*/

	ordena(numeros, lim);

	printf("\n ordenados\n");
	for(i=0; i <= lim; i++) printf("%d\n", numeros[i]); //imprime numeros ordenados


}
