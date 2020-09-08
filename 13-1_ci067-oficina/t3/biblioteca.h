#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TAM 10000 /*numero de caracteres p/ enunciados da questao e alternativa*/

typedef struct ALTERNATIVA{
	char *enunciado_alternativa; /*enunciado da alternativa*/
	char resposta; /*(F) verdadeiro ou (F) falso*/
	int peso; /*definido pelo outro programa "execucao"*/
	struct ALTERNATIVA *proxima_alternativa; /*proximo item da lista*/
}ALTERNATIVA; /*tipo abstrato p/ alternativa*/

typedef struct QUESTAO{
	char *enunciado_questao;
	ALTERNATIVA *conjunto_alternativas; /*cabeca da lista do tipo ALTERNATIVA*/
	int soma_resposta; /*soma dos pesos das questoes corretas*/
	int ordem; /*numero da questao*/
	struct QUESTAO *questao_seguinte;
}QUESTAO; /*tipo abstrato p/ questao*/

typedef struct PROVA{
	QUESTAO *primeira_questao;
	QUESTAO *ultima_questao;
	int numero_questoes;
}PROVA; /*header p/ a prova*/

QUESTAO *adiciona_questao(void); /*1) aloca espaco p/ um item da lista de questoes, inicializa os objetos do item, retorna o endereco deste espaco*/

ALTERNATIVA *adiciona_alternativa(void); /*2) aloca espaco p/ um item da lista de alternativas, inicializa os objetos do item, retorna o endereco deste espaco*/

void remove_questao(QUESTAO *anterior_removida); /*3) remove um noh da lista de questoes*/

void edita_enunciado_questao(QUESTAO *pergunta); /*4) recebe o enunciado da questao*/

void edita_alternativa(ALTERNATIVA *opcao); /*5) recebe o enunciado e a resposta da alternativa*/

void concatena_caracter_string(char constante[], char caracter); /* 6) insere o carater (char) ao final da constante de caracteres (char[])*/

/* 1) =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
QUESTAO *adiciona_questao(void){
	QUESTAO *nova; /*declaro um ponteiro auxiliar que vai receber o endereco do espaco alocado p/ o item da lista de questoes (tipo QUESTAO)*/
	nova = (QUESTAO *) malloc(sizeof(QUESTAO)); /*aloco espaco p/ um item do struct tipo QUESTAO*/
	if(!nova) return NULL; /*testa se foi possivel alocar*/
	
	nova->enunciado_questao = NULL; /*inicializa os objetos*/
	nova->conjunto_alternativas = NULL;
	nova->soma_resposta = 0;
	nova->questao_seguinte = NULL;
	
	return nova; /*retorna o endereco do item alocado*/
} /*aloca espaco p/ um item da lista de questoes, inicializa os objetos do item, retorna o endereco deste espaco*/
/* 2) =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
ALTERNATIVA *adiciona_alternativa(void){
	ALTERNATIVA *opcao; /*declaro um ponteiro auxiliar que recebe o endereco do item (tipo ALTERNATIVA)*/
	opcao = (ALTERNATIVA*) malloc(sizeof(ALTERNATIVA)); /*aloco espaco*/
	if(!opcao) return NULL; /*testa se foi possivel alocar*/
	
	opcao->enunciado_alternativa = NULL; /*inicializa os objetos*/
	opcao->resposta = '\0';
	opcao->peso = 0;
	opcao->proxima_alternativa = NULL;
	
	return opcao; /*retorna o endereco do item  (tipo ALTERNATIVA) que contem a opcao de resposta*/
} /*aloca espaco p/ um item da lista de alternativas, inicializa os objetos do item, retorna o endereco deste espaco*/
/* 3) =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
void remove_questao(QUESTAO *anterior_removida){
	QUESTAO *auxiliar;
	auxiliar = anterior_removida->questao_seguinte; /*pega o endereco do item removido*/
	anterior_removida->questao_seguinte = auxiliar->questao_seguinte; /*o item anterior a "removida" passa a apontar p/ o seguinte a "removida"*/
	free(auxiliar); /*libera o espaco ocupado pelo noh removido*/
} /*remove um noh da lista de questoes*/
/* 4) =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
void edita_enunciado_questao(QUESTAO *pergunta){
	pergunta->enunciado_questao = (char*) malloc(MAX_TAM*sizeof(char)); /*aloco um vetor "grande" para receber o enunciado*/
	printf("Digite o enunciado da questão (máximo %d caracteres): ", MAX_TAM);
	fgets(pergunta->enunciado_questao, MAX_TAM, stdin); /*fgets() pega ate o quebra-linha e coloca um terminador nulo na posicao seguinte*/
	
	int tamanho_enunciado;
	tamanho_enunciado = strlen(pergunta->enunciado_questao); /*tamanho real do enunciado (enunciado + quebra-linha)*/
	pergunta->enunciado_questao[tamanho_enunciado] = '\0'; /*coloca um terminador nulo na ultima posicao "valida" (que tem um quebra-linha), antes do nulo colocado por fgets()*/
	pergunta->enunciado_questao = (char *) realloc(pergunta->enunciado_questao, tamanho_enunciado * sizeof(char)); /*realoca o vetor do enunciado p/ o tamanho real*/
} /*recebe o enunciado da questao*/
/* 5) =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
void edita_alternativa(ALTERNATIVA *opcao){
	opcao->enunciado_alternativa = (char*) malloc(MAX_TAM*sizeof(char)); /*aloco um vetor "grande" para receber o enunciado*/
	printf("Digite o enunciado da alternativa (máximo %d caracteres): ", MAX_TAM);
	fgets(opcao->enunciado_alternativa, MAX_TAM, stdin); /*fgets() pega ate o quebra-linha e coloca um terminador nulo na posicao seguinte*/

	int tamanho_enunciado;
	tamanho_enunciado = strlen(opcao->enunciado_alternativa); /*tamanho real do enunciado (enunciado + quebra-linha)*/
	opcao->enunciado_alternativa[tamanho_enunciado] = '\0'; /*coloca um terminador nulo na ultima posicao "valida", antes do nulo colocado por fgets()*/
	opcao->enunciado_alternativa = (char *) realloc(opcao->enunciado_alternativa, tamanho_enunciado * sizeof(char)); /*realoca o vetor do enunciado p/ o tamanho real*/
	
	printf("Resposta ('V' ou 'F'): ");
	opcao->resposta = toupper(getchar());
	getchar(); /*limpar o buffer*/
} /*recebe o enunciado e a resposta da alternativa*/
/* 6) =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
void concatena_caracter_string(char constante[], char caracter){
	int tamanho;
	tamanho = strlen(constante);
	constante[tamanho+1] = caracter;
} /*insere o carater (char) ao final da constante de caracteres (char[])*/
