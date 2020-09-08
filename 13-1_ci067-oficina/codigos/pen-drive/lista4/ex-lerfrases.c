#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINHAS 5
#define COLUNAS 100

int main(){
	char endereco[] = "ex4_oficina.dat";
	FILE *fp;

	fp = fopen(endereco, "r");

	if(!fp) printf("Erro na abertura do arquivo.\n");
	else printf("Arquivo aberto com sucesso.\n");

	char texto[LINHAS][COLUNAS];
	fread(texto, sizeof(char), LINHAS*COLUNAS, fp);

	fclose(fp);

	int i;
	for(i=0; i<LINHAS; i++){
		printf("%s", texto[i]);
	}
}
