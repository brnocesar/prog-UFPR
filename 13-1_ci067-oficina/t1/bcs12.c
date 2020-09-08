#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define P 6 /*5 casas + nulo*/
#define N 20 /*maximo de jogadas*/
#define M 8 /* tamanho do vetor que guarda o tipo de movimento: "salta" ou "desliza", + nulo*/

struct plano{
	char tabuleiro[P];
	char movimento[M];
};


int imprime_plano(struct plano jogo_terminado[], int tam){
	int i;
	
	for(i=0; i<tam; i++){
		printf("%s:\t", jogo_terminado[i].movimento);
		printf("_%s_\n", jogo_terminado[i].tabuleiro);
	}
	
	exit(1);
}

int repetida(struct plano jogadas[], char candidato[], int lim){
	int i;
	
	for(i=0; i<lim; i++){
		if(!strcmp(jogadas[i].tabuleiro, candidato)) return 1; /*retorna NAO-ZERO se ENCONTRAR a jogada*/
	}
	
	return 0; /*retorna ZERO se NAO ENCONTRAR a jogada*/
}

int joga(char tabuleiro_final[], struct plano vetor_plano[], int indice_jogada){
	
	if(!strcmp(tabuleiro_final, vetor_plano[indice_jogada].tabuleiro)) imprime_plano(vetor_plano, indice_jogada); /*se as strings forem iguais, chama funcao que imprime o plano de jogo*/
	
	
	if(repetida(vetor_plano, vetor_plano[indice_jogada].tabuleiro, indice_jogada)) return 0; /*verifica se a jogada eh repetida ...........????????????????????????? */
	
	
	strcpy(vetor_plano[indice_jogada].tabuleiro, vetor_plano[indice_jogada - 1].tabuleiro); /*copia o tabuleiro anterior p/ o atual*/
	
	
	int movimentos_possiveis; /*verifica o numero de movimentos possiveis pela posicao da casa vazia, "espaco em branco"*/
	if((vetor_plano[indice_jogada].tabuleiro[0] == ' ')||(vetor_plano[indice_jogada].tabuleiro[P-2] == ' ')) movimentos_possiveis = 2;
	else if((vetor_plano[indice_jogada].tabuleiro[1] == ' ')||(vetor_plano[indice_jogada].tabuleiro[P-3] == ' ')) movimentos_possiveis = 3;
	else if (vetor_plano[indice_jogada].tabuleiro[2] == ' ') movimentos_possiveis = 4;
	
	
	int i, opcao_movimento; /*indice p/ andar pelo tabuleiro*/
	opcao_movimento = 0;
	while(movimentos_possiveis > 0){
		i = 0;
		/*bloco de comandos que faz a jogada*/
		while(i < (P-1)){
			
			if(vetor_plano[indice_jogada].tabuleiro[i] == ' '){
				i++;
				continue;
			} /*verifica se a posicao ta vazia*/
			
			/*condicao p/ deslizar*/
			else if((vetor_plano[indice_jogada].tabuleiro[i+1] == ' ')||(vetor_plano[indice_jogada].tabuleiro[i-1] == ' ')){
				if((i == 0)||(i == 1)||(i == 2)||(i == 3)){
					vetor_plano[indice_jogada].tabuleiro[i+1] = vetor_plano[indice_jogada].tabuleiro[i];
					strcpy(vetor_plano[indice_jogada].movimento, "desliza"); /*p/ frente*/
					vetor_plano[indice_jogada].tabuleiro[i] = ' ';
					break; /*se executa o movimento, sai do laco que anda pelo tabuleiro*/
				}
				else if((i == 1)||(i == 2)||(i == 3)||(i == 4)){
					vetor_plano[indice_jogada].tabuleiro[i-1] = vetor_plano[indice_jogada].tabuleiro[i];
					strcpy(vetor_plano[indice_jogada].movimento, "desliza"); /*p/ tras*/
					vetor_plano[indice_jogada].tabuleiro[i] = ' ';
					break; /*se executa o movimento, sai do laco que anda pelo tabuleiro*/
				}
			}
			
			/*condicao p/ saltar*/
			else if((vetor_plano[indice_jogada].tabuleiro[i+2] == ' ')||(vetor_plano[indice_jogada].tabuleiro[i-2] == ' ')){
				if((i == 0)||(i == 1)||(i == 2)){
					if(vetor_plano[indice_jogada].tabuleiro[i] == vetor_plano[indice_jogada].tabuleiro[i+1]){
						i++;
						continue;
					} /*evita que uma ficha salte sobre a irma, NAO FAZ MOVIMENTO, continua pra proxima casa*/
					else
						vetor_plano[indice_jogada].tabuleiro[i+2] = vetor_plano[indice_jogada].tabuleiro[i];
						strcpy(vetor_plano[indice_jogada].movimento, "salta"); /*p/ frente*/
						vetor_plano[indice_jogada].tabuleiro[i] = ' ';
						break;
				}
				else if((i == 2)||(i == 3)||(i == 4)){
					if(vetor_plano[indice_jogada].tabuleiro[i] == vetor_plano[indice_jogada].tabuleiro[i-1]){
						i++;
						continue;
					} /*evita que uma ficha salte sobre a irma*/
					else
						vetor_plano[indice_jogada].tabuleiro[i-2] = vetor_plano[indice_jogada].tabuleiro[i];
						strcpy(vetor_plano[indice_jogada].movimento, "salta"); /*p/ tras*/
						vetor_plano[indice_jogada].tabuleiro[i] = ' ';
						break;
				}
			}
			
			i++;
		}
		
		
		joga(tabuleiro_final, vetor_plano, indice_jogada + 1); /*chamada recursiva*/
		
		
		movimentos_possiveis--;
	} /*FIM - while, movimentos possiveis*/
	
} /*FIM - funcao joga*/

int main(){
	char entrada[P], saida[P], c;
	int i;
	struct plano vetor_plano_main[N]; //declaro um vetor de estrutura do "TIPO plano" com "NOME vetor_plano_main"
	
	/*recebe os caracteres e coloca no vetor, nao coloca o ponto no vetor*/
	printf("Entre com o estado inicial: ");
	for(i=0; (i < P) && ((c = getchar()) != '.'); i++) entrada[i] = c;
	getchar();
	printf("Entre com o estado final: ");
	for(i=0; (i < P) && ((c = getchar()) != '.'); i++) saida[i] = c;
	getchar();
	
// 	entrada[5] = 0;
    saida[5] = 0; /*coloca o terminador nulo na ultima posicao do vetor, por garantia*/
	
//	printf("_%s_\n", entrada);
//	printf("_%s_\n", saida); /*teste de impressao*/

	int indice_jogada;
	indice_jogada = 0;
	strcpy(vetor_plano_main[indice_jogada].tabuleiro, entrada);
	strcpy(vetor_plano_main[indice_jogada].movimento, "inicial");

	joga(saida, vetor_plano_main, indice_jogada + 1);
	
	
	
	return 0;
}