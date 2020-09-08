#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *palavra;
	int npalavra;
	int *linha;
}lista;

/*variaveis globais(INICIO)*/
int linha_contador;
/*variaveis globais(FIM)*/


void escrita(){
	/*escreve no arquivo, chamada pela main*/
}


void troca(int a, int b){
	/*troca os enderecos das palavras*/
// 	char *p_aux;
// 	p_aux = lista.palavra[a];
// 	lista.npalavra[a] = lista.npalavra[b];
// 	lista.palavra[b] = aux;
	
	/*troca a frequencia da palavra no arquivo*/
// 	int n_aux;
// 	n_aux = lista.npalavra[a];
// 	lista.npalavra[a] = lista.npalavra[b];
// 	lista.npalavra[b] = n_aux;
	
	/*troca o numero de ocorrencias relativas a cada linha*/
// 	int *l_aux;
// 	l_aux = lista.linha[a];
// 	lista.linha[a] = lista.linha[b];
// 	lista.linha[b] = l_aux;
	
} /*troca os elementos da estrutura dos indices que recebe*/


void ordena(int local, int indice_final){
	/*coloca a palavra no devido local, usa funcao troca(int a, int b)*/
}


void insere(char palavra[], int posicao){
	/* IF a palavra ja ta na estrutura, incrementa;
	 * ELSE realoca mais espaco na estrutura e coloca na ultima posicao, chama ordena().
	 */
}

void busca(char palavra[]){
	/* recursiva;
	 * recebe uma palavra, que leitura pegou;
	 * procura a palavra na estrutura:
	 * * encontra a posicao da palavra na estrutura, ou a posicao que deveria estar
	 * chama funcao insere(), passa a palavra e o indice (posicao).
	 */
//	insere(palavra, local);
	
	
}


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
//			printf("\n"); /*teste*/
			linha_contador++;
			continue;
		}
		else{															
			if(strlen(palavra) == 0) continue;
//			printf(" %s", palavra);						/*teste de impressao, palavra COMPLETA*/
//			busca(palavra); /*chama funcao que procura a palavra na strutura*/ /**************************************************************************/
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
