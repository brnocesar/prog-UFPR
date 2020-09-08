#include <stdio.h>
#define N 30

int obtem_vetor(int vetor[], int tamanho, int parada){
	int i, elementos_lidos;
	elementos_lidos = 0;
	
	for(i=0; i<tamanho; i++){
		scanf("%d", &vetor[i]);
		if(vetor[i] == parada) return elementos_lidos;
		elementos_lidos++;
	}
	return elementos_lidos;
}

int main(){
	int tamanho_usuario, array[N], condicao_parada;
	
	printf("digite o tamanho maximo do vetor (maximo %d): ", N);
	scanf("%d", &tamanho_usuario);
	if(tamanho_usuario > N) tamanho_usuario = N;
	
	printf("digite a condicao de parada (um inteiro): ");
	scanf("%d", &condicao_parada);
	
	printf("foram lidos %d elementos.\n", obtem_vetor(array, tamanho_usuario, condicao_parada));
}