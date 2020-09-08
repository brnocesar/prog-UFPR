#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100

int main(){
	char string[N];
	int numeros[N], i, lim, c;

	/*recebe uma string usando getchar*/
	char coluna[N][1];
	printf("digite uma string: ");
	for(i=0; i<N && (c = getchar()) != '\n'; i++){
		coluna[i][1] = c;
		//coluna[i][2] = 0;
	}
	coluna[i][1] = 0; /*coloca o terminador nulo na ultima linha da coluna*/

	int cont;
	cont = 0;
	i = 0;
	while(coluna[i][1] != '\0'){
		printf("%c\n", coluna[i++][1]);
		cont++;
	}

	char ordenado[N];

//	ordenado[i] = coluna[i]


	i = 0;
	while(i < cont){
		printf("\t%d\n", strcmp(coluna[i], coluna[++i]));
	}



}
