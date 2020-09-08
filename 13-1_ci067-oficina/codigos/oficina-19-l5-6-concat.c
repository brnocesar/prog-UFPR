#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

char *concat(char *str1, char *str2){
	
	char *local; /*declaro um ponteiro que vai receber o espaço alocado*/
	
	local = (char *) malloc((2*N)*sizeof(char)); /*aloca espaço para 100 (2xN) caracteres do tipo char*/
	
	if(local == NULL){
		printf("espaco nao alocado!");
		exit(1);
	}
	
	strcpy(local, str1); /*copio o conteudo de str1 para local*/
	
	int i;
	i = strlen(local); /*i recebe o numero de caracteres validos em local*/
	*(local + (i-1)) = 0; /*substitui o quebra-linha por um nulo*/
	strcat(local, str2); /*concatena str2 em local*/

	printf("(concat) %s", local); /*teste*/

	return local; /*retorna o endereço do espaço com as strings concatenadas*/
}


int main(){
	char primeira[N], segunda[N];

	printf("digite duas strings: ");
	fgets(primeira, N-2, stdin);
	fgets(segunda, N-2, stdin);
	
//	printf("\t %s \n\t %s", primeira, segunda); /*teste*/

	char *resultado;
	resultado = concat(primeira, segunda);
	
	printf("(main) %s.", resultado);
}