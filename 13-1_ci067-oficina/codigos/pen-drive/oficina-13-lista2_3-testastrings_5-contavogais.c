#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int contavogais(char s[]){
	int vogais, i;
	
	vogais = 0;
	i=0;
	while(s[i] != '\n'){
		if((s[i] == 'a')||(s[i] == 'e')||(s[i] == 'i')||(s[i] == 'o')||(s[i] == 'u')) vogais++;
		i++;
	}
	
	return vogais;
}

int mstrlen(char s[]){
	int tam;
	
	tam = 0;
	while(s[tam] != '\n'){
		tam++;
	}
	
	return tam;
} //calcula o tamanho de "s", exceto o terminador nulo

int mstrcmp(char s[], char t[]){
	if(mstrlen(s) < mstrlen(t)) return -1; /*primeira menor que segunda*/
	if(mstrlen(s) == mstrlen(t)) return 0; /*strings iguais*/
	if(mstrlen(s) > mstrlen(t)) return +1; /*primeira maior que segunda*/
}

int main(){
	char caneta[N], lapis[N];
	printf("digite uma palavra, frase ou serie de caracteres: ");
	fgets(caneta, N, stdin); /*fgets(vetor, numero_maximo_caracteres, referencia ao input (pelo teclado)*/
	printf("digite outra palavra, frase ou serie de caracteres: ");
	fgets(lapis, N, stdin); /*esta funcao adiciona o "quebra linha" no caracter anterior ao terminador nulo*/
	
	printf("$ a string\n%spossui tamanho %d.\n", caneta, mstrlen(caneta));
	printf("$ a string\n%spossui tamanho %d.\n\n", lapis, mstrlen(lapis));
	
	if(mstrcmp(caneta, lapis) == -1) printf("a segunda eh maior.\n\n");
	if(mstrcmp(caneta, lapis) == 0) printf("sao iguais.\n\n");
	if(mstrcmp(caneta, lapis) == +1) printf("a segunda eh menor.\n\n");
	
	printf("$a string\n%spossui %d vogais.\n", caneta, contavogais(caneta));
	printf("$a string\n%spossui %d vogais.\n\n", lapis, contavogais(lapis));
	
	return 0;
}

