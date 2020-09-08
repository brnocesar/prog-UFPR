/* teste de uma funcao recursiva que:
 * 1) recebe o endereço de um arquivo;
 * 2) pega uma, e somente uma, palavra deste arquivo;
 * 3) passa todos os caracters desta palavra para minusculo;
 * 4) passa a palavra como argumento de uma funcao que busca na estrutura.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /*tolower()*/


/*variaveis globais*/
int linha_contador;


void leitura(char *arquivo){
	
	FILE *fp;
	
	fp = fopen(arquivo, "r"); /*abre o arquivo APENAS p/ leitura*/
	
	if(fp == NULL){
		printf("Erro! Impossível abrir arquivo\n");
		exit(2);
	}
	
	linha_contador = 0; /*inicializa contador de linhas do arquivo, variavel global*/
	
 	char aux, *palavra;
	palavra = (char *) calloc(2, sizeof(char)); /*alocando espaco p/ 50 elementos char, zerando os elementos*/
	aux = tolower(getc(fp));
	*(palavra + 0) = aux;

	int i; i=1; /*inicia contador no indice UM pois ja ocupou o primeiro elemento*/
	while(feof(fp) == 0){
 		
		aux = tolower(getc(fp)); /*getc() pega um caracter do arquivo e tolower() converte para minuscula*/
		
		if((aux >= 'a' && aux <= 'z')||(aux >= '1' && aux <= '9')){
			palavra = (char *) realloc(palavra, (i+2)*sizeof(char)); /*realoco espaco p/ mais um elemento*/
			*(palavra + (i+1)) = *(palavra + i); /*coloca o '\0' na ultima posicao*/
			*(palavra + i) = aux; /*coloca o caracter no ultimo elemento valido*/
//			printf("%s ", palavra); /*teste de impressao, palavra INCOMPLETA*/
			i++;
			continue;
		}
		else if(aux == '\n'){
			printf("\n"); /*teste*/
			linha_contador++;
			continue;
		}
		else{															
			if(strlen(palavra) == 0) continue;
			printf(" %s", palavra);						/*teste de impressao, palavra COMPLETA*/
//			busca(palavra); /*chama funcao que procura a palavra na strutura*/
			i=0;
			free(palavra);
			palavra = (char *) calloc(2, sizeof(char));
		} /*pegou um caracter nao valido (pontuacao)*/
		
 	}
 	
	
	fclose(fp);
}


int main(int argc, char *argv[]){
	/* argv[0] eh o proprio nome do programa (executal);
	 * argv[1] eh o nome do documento (arquivo) a ser indexado.*/
	
	if(argc != 2){
		printf("Forma de uso: %s arquivo\n", argv[0]);
		exit(1);
	}
	else
		leitura(argv[1]);

}