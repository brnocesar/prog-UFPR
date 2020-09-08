#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

void copia(char str1[], char str2[]){
	char aux[N];
	int i, tam1, tam2;
	tam1 = strlen(str1);
	tam2 = strlen(str2);

	for(i=0; i<tam1; i++){
		aux[i] = str1[i];
	}
	aux[tam1] = 0;
	
	for(i=0; i<tam2; i++){
		str1[i] = str2[i];
	}
	str1[tam2] = 0;

	for(i=0; i<tam1; i++){
		str2[i] = aux[i];
	}
	str2[tam1] = 0;
}


int main(){
	char primeira[N], segunda[N];

	printf("digite duas palavras: ");
	fgets(primeira, N-1, stdin);
	fgets(segunda, N-1, stdin);

	printf(" 1) %s", primeira);
	printf(" 2) %s", segunda);
	copia(primeira, segunda);
	printf(" 1) %s", primeira);
	printf(" 2) %s", segunda);
}
