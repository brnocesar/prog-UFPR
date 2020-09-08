#include <stdio.h>

#define MAX 500

main(){

  	int fr;
  	char dado[MAX], *arquivo = "teste.txt";
  	FILE *arq;
  
  	arq= fopen(arquivo, "r+");

	if(!arq) printf("Erro na abertura do arquivo.");
	    else printf("Arquivo aberto com sucesso.");

  	fr = fread(dado, sizeof(char), MAX, arq);

  	printf ("\nForam lidos %d caracteres do arquivo \"%s\".\n", fr, arquivo);
	dado[MAX] = 0;
	printf("\n%s\n\n", dado);

  	fclose(arq);

}
