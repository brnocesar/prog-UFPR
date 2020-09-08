#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int main(){
	char arquivo[] = "ex4_oficina.dat";
	FILE *fp;
	
	fp = fopen(arquivo, "w");

	if(!fp) printf("Erro na abertura do arquivo.\n");
	else printf("Arquivo aberto com sucesso.\n");


	char vetor[N];
	int i;

	for(i=0; i<5; i++){
		printf("digite uma frase: ");
		fgets(vetor, N-1, stdin);
		fprintf(fp, " %s\n", vetor);
	}


	fclose(fp);
}
