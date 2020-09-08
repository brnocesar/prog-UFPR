#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

int main(){
	char endereco[] = "arquivo_6.dat";
	FILE *fp;

	fp = fopen(endereco, "r");

	if(!fp) printf("erro ao abrir o arquivo!\n");
	else printf("\tarquivo aberto com sucesso!\n");

	int vetor[N];

	fread(vetor, sizeof(int), N, fp);


	fclose(fp);

	int i;
	for(i=0; i<N; i++) printf(" %d\n", vetor[i]);
}
