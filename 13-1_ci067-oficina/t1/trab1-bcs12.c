#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define P 20 /*(P-1) casas de jogo + nulo*/
#define N 100 /*maximo de jogadas*/
#define M 8 /* tamanho do vetor que guarda o tipo de movimento: "salta" ou "desliza", + nulo*/

struct plano{
	char tabuleiro[P];
	char movimento[M];
}; /*define um struct do tipo "plano", que contem dois strings: um para o estado do tabuleiro e outro para o tipo de movimento*/


int imprime_plano(struct plano jogo_terminado[], int tam){
	int i;
	
	for(i=0; i<tam; i++){
		printf("(%d) ", i);
		printf("%.8s:	", jogo_terminado[i].movimento);
		printf("_%s_\n", jogo_terminado[i].tabuleiro);
	}
	
	exit(1);
} /*imprime o plano de jogo, todas as jogadas ateh o estado final*/


int repetida(struct plano jogadas[], char candidato[], int lim){
	int i;
	
	for(i=0; i<lim; i++){
		if(!strcmp(jogadas[i].tabuleiro, candidato)) return 1; /*retorna NAO-ZERO se ENCONTRAR a jogada*/
	}
	
	return 0; /*retorna ZERO se NAO ENCONTRAR a jogada*/
} /*verifica se a jogada ja foi feita*/


void executa_jogada(struct plano vetor_plano[], int indice_jogada, int a, int b){
	int aux;
	
	aux = vetor_plano[indice_jogada].tabuleiro[a];
	vetor_plano[indice_jogada].tabuleiro[a] = vetor_plano[indice_jogada].tabuleiro[b];
	vetor_plano[indice_jogada].tabuleiro[b] = aux;
	
	if(fabs(a-b) == 1) strcpy(vetor_plano[indice_jogada].movimento, "desliza");
	else
		strcpy(vetor_plano[indice_jogada].movimento, "salta");
} /*executa a jogada, move a peça trocando os caracteres de lugar e define o tipo de movimento pela distancia dsa casas*/


int procura_jogada(int tamanho, char tabuleiro_final[], struct plano vetor_plano[], int indice_jogada){
	
	if(!strcmp(tabuleiro_final, vetor_plano[indice_jogada - 1].tabuleiro)) imprime_plano(vetor_plano, indice_jogada); /*se as strings forem iguais, chama funcao que imprime o plano de jogo*/
	
	if(indice_jogada > N){
		printf("Solução não encontrada.\n");
		exit(2);
	}
	
	strcpy(vetor_plano[indice_jogada].tabuleiro, vetor_plano[indice_jogada - 1].tabuleiro); /*copia o tabuleiro anterior p/ o atual*/
	
	
	int i, j;
	for(i=0; i<tamanho; i++){
		if(vetor_plano[indice_jogada].tabuleiro[i] != ' ') continue; /*quando achar o caracter ' ', executa o for() interno*/
		for(j = i-2; j <= i+2; j++){
			if(j<0 && j>(tamanho-1)) continue; /*verifica se o indice j, "casa de jogo", ta dentro do tabuleiro*/
			
			executa_jogada(vetor_plano, indice_jogada, i, j);/*chama funcao que executa a jogada e define o tipo de movimento*/
			
            if(repetida(vetor_plano, vetor_plano[indice_jogada].tabuleiro, indice_jogada)){
                strcpy(vetor_plano[indice_jogada].tabuleiro, vetor_plano[indice_jogada - 1].tabuleiro);
                continue;
            } /*verifica se ta repetindo uma jogada, se verdade, re-monta o tabuleiro com o estado anterior*/
			
			procura_jogada(tamanho, tabuleiro_final, vetor_plano, indice_jogada + 1); /*chamada recursiva*/
			
			strcpy(vetor_plano[indice_jogada].tabuleiro, vetor_plano[indice_jogada - 1].tabuleiro);
			/*se chegou ateh aqui, significa que o caminho nao eh adequado, continua o loop*/
		}
		return 1; /*se chegou ateh aqui, significa que o caminho nao eh adequado, retorna NAO-ZERO pra instancia que chamou*/
	}
}


int recebe(char inicio[], char final[]){
	char c;
	int i;
	printf("Entre com o estado inicial (maximo: %d casas): ", P-1);
	for(i=0; (i < P) && ((c = getchar()) != '.'); i++) inicio[i] = c; /*recebe cada caracter e coloca no vetor, para quando recebe o "'.'" ou excede o tamanho*/
	getchar(); /*pega o quebra-linha*/	
	inicio[i] = 0; /*coloca o terminador nulo na string que usuario forneceu*/

	printf("Entre com o estado final (%d casas): ", i); /*pede uma string do tamanho da primeira que entrou*/
	fgets(final, i+1, stdin); /*fgets() recebe o ponto, mas o "sobrescreve" com o terminador nulo na ultimo posicao*/
	
	return i;
}



int main(){
	char entrada[P], saida[P];
	int tamanho;
	struct plano vetor_plano_main[N]; //declaro um vetor de estrutura do "TIPO plano" com "NOME vetor_plano_main"
	
	tamanho = recebe(entrada, saida);	

	int indice_jogada;
	indice_jogada = 0;
	strcpy(vetor_plano_main[indice_jogada].tabuleiro, entrada);
	strcpy(vetor_plano_main[indice_jogada].movimento, "inicial");

	procura_jogada(tamanho, saida, vetor_plano_main, indice_jogada + 1);
	
	return 0;
}
