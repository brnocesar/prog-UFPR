#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char arquivo[] = "lista5-ex8.dat";
	FILE *fp;
	
	fp = fopen(arquivo, "w+");
	
	if(!fp) printf("erro ao abrir arquivo!\n");
	else printf("arquivo aberto com sucesso!\n");
	
	
	char c, *espaco; /*variavel temporaria p/ char*/
	c = getc(fp);
	int i;
	i = 1;
	espaco = (char*) calloc(i, sizeof(char));
	
	while(!feof(fp)){
		strcat(espaco, c); /*concatena o ultimo caracter pego do arquivo ao final do espaço que vai sendo realocado*/
		i++; /*incrementa o numero de caracteres*/
		espaco = (char*) realloc(espaco, i*sizeof(char)); /*realoca espaço para mais um char*/
		c = getc(fp); /*le um novo caracter no arquivo*/
	} /*feof() retorna ZERO enquanto nao chega ao fim do arquivo*/
	
	fclose(fp);
	
	printf("%s ", espaco);
	
}