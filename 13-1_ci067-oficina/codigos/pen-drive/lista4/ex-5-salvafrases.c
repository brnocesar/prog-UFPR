#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLUNAS 100
#define LINHAS 5

int main(){
	char arquivo[] = "ex4_oficina.dat";
	FILE *fp;
	
	fp = fopen(arquivo, "w");

	if(!fp) printf("Erro na abertura do arquivo.\n");
	else printf("Arquivo aberto com sucesso.\n");


	char tabela[LINHAS][COLUNAS];
	int i;
	i=0;
	while(i < LINHAS){
		printf("digite a frase (%d): ", i+1);
		fgets(tabela[i], COLUNAS-1, stdin);
		fprintf(fp, "%s", tabela[i]);
		i++;
	}

	/*teste de impressao*/
	for(i=0; i<LINHAS; i++){
		printf("\t%s", tabela[i]);
		
	}

	fclose(fp);
}
