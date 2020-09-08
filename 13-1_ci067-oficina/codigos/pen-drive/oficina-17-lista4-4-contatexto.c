#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char arquivo[] = "teste.dat";
	FILE *fp;

	fp = fopen(arquivo, "r");

	if(!fp) printf("Erro na abertura do arquivo.\n");
	else printf("Arquivo aberto com sucesso.\n");
	
	int linhas, palavras, caracteres;
	linhas = 0;
	palavras = 0;
	caracteres = 0;

	char c;
	c = getc(fp);
	while(!feof(fp)){
		int estado;
		printf("%c", c); /*imprime o caracter na tela*/
		c = getc(fp); /*le um novo caracter no arquivo*/

		caracteres++;

		if(c == '\n') linhas++;

		if((c == '\n')||(c == ' ')||(c == '\t')){
			if(estado == 0){
				estado--;
				continue;
			}
			else estado = 0;
		}
		else{
			if(estado >= 0) estado++;
			else estado = 1;
		}

		if(estado == 0) palavras++;
	} /*feof() retorna zero enquanto nao chega ao fim do arquivo*/
	
	printf("\n");
	printf("linhas: %d\n", linhas);
	printf("palavras: %d\n", palavras);
	printf("caracteres: %d\n", caracteres);
	
	fclose(fp);
}
