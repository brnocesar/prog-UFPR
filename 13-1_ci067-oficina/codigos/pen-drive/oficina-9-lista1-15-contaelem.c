//incompleto, errado
#include <stdio.h>
#define N 12

int contaelem(char vetor[], char comp){
	int ocorrencias, i;
	ocorrencias = 0;
	
	for(i=0; i<(N-1); i++){
		if(comp == vetor[i]) ocorrencias++;
	}
	
	return ocorrencias;
}

int main(){
	char array[N], letra;
	int i;
	
	printf("digite uma letra para comparar: ");
	scanf("%s", &letra);
	
	printf("digite %d elementos:\n", N);
	for(i=0; i<(N-1); i++){
		scanf("%c", &array[i]);
	}
	array[N-1] = '\0';
	
	printf("a letra '%c' aparece %d vezes no vetor\n", letra, contaelem(array, letra));
	for(i=0; i<N; i++) printf(" %c ", array[i]);
	return 0;
}