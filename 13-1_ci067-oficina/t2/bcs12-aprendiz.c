#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 11 /*numero de casas do tabuleiro, + quebra-linha, + terminador nulo*/


typedef struct jogador{
	char especie; /* 'M' p/ maquina, 'H' p/ humano*/
	char marcador; /* 'X' se sair jogando, 'O' se for o segundo*/
}jogador;

typedef struct JOGADA{
	char autor; /* autor da jogada (jogador): 'M' p/ maquina, 'H' p/ humano*/
	char tabuleiro[N];
	int num_casa; /*numero de casas ocupadas no tabuleiro, ordem da jogada*/
	struct JOGADA **jogada_primaria_partida; /*aponta p/ o primeiro item da lista*/
	struct JOGADA *proxima_jogada; /*aponta para jogada seguinte*/
}JOGADA;

typedef struct PARTIDA{
	JOGADA *cabeca_partida; /*endereço do struct que contem a primeira jogada*/
	struct PARTIDA **lider;
	struct PARTIDA *proxima_partida;
}PARTIDA;
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ DEFINICAO DOS TIPOS ABSTRATOS DE DADOS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */


PARTIDA *pega_arquivo(); /*se o arquivo especificado na fucao existir, pega o seu conteudo e coloca na estrutura, retorna um ponteiro p/ a cabeca da lista de partidas*/

PARTIDA *insere_item_lista(PARTIDA **cabeca); /*adiciona um novo item (no final) na lista, retorna um ponteiro p/ este novo item*/

JOGADA *cria_partida(JOGADA **jogada_primaria); /*cria uma lista com itens do tipo JOGADA, retorna um pontiero p/ o primeiro item da lista*/

void ordem_jogadas_arq(jogador *primeiro, jogador *segundo, char primespecie); /*define a vez (jogada 'par' ou 'impar') de cada jogador ('H' ou 'M')*/

JOGADA *insere_item_jogada(JOGADA *anterior); /*adiciona um novo item (no final) na lista, retorna um ponteiro p/ este novo item*/

int procura_char(char string[], char caracter); /*recebe uma string e um caracter, se este caracter existir na string retorna 1 (NAO-ZERO, verdade), senao retorna 0 (zero, falso)*/

void ordem_jogadas_user(jogador *primeiro, jogador *segundo); /*define a ordem de quem faz as jogadas ('M' ou 'H') e qual o marcador ('X' ou 'O')*/

JOGADA *cria_partida_jogada(); /*retorna um ponteiro p/ o primeiro item da lista de jogadas*/

int realiza_movimento(PARTIDA **cabeca_partidas, jogador *primeiro, jogador *segundo, JOGADA *lista_mov, int indice); /*recursiva, define quem joga ('H' ou 'M') e verifica quem (se) ganhou*/

void recebe_jogada_humano(jogador *jogador_humano, JOGADA *jogada_partida, int indice_jogadas); /*recebe o tabuleiro do usuario pela entrada padrao*/

void jogada_maquina(PARTIDA **cabeca_partidas, jogador *jogador_maquina, JOGADA *jogada_partida, int indice_jogadas); /*maquina faz jogada em que chance de perder eh menor */

int compara_jogadas(PARTIDA *cabeca_partida, char provavel_saida[]); /*funcao que recebe o tabuleiro do usuario e ponteiro p/ cabeca da estrutura, LOCALIZA os devidos itens na estrutura p/ comparar com a provavel jogada*/

char *troca_marcadores(char tabuleiro_trocado[]); /*troca os marcadores ('X' e 'O') de um tabuleiro*/

int casas_ocupadas(char campo_jogo[]); /*retorna o numero de casas ocupadas no tabuleiro*/

int verifica_vitoria(char iniciante, char tabuleiro[]); /*se humano vence retorna '1', se maquina vence retorna '-1', se da velha retorna '0'*/

int apaga_partida(JOGADA *primeira_jogada_apaga); /*libera o espaco ocupado pela lista de jogadas*/
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- DECLARACAO/CABECALHOS DAS FUNCOES -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */


JOGADA *cria_partida_jogada(){
	JOGADA *nova; /* declara um ponteiro p/ uma strutura do "TIPO: JOGADA" com "NOME: nova"*/
	nova = (JOGADA*) malloc(sizeof(JOGADA)); /*aloca espaco p/ um item (estrutra) do tipo JOGADA, e retorna o endereco p/ nova*/
	if(!nova) return NULL; /*testa se foi possivel alocar*/
	
	/*inicializa os objetos*/
	nova->autor = '\0';
	int t;
	for(t=0; t<(N-1); t++) nova->tabuleiro[t] = '_';
	nova->tabuleiro[N] = '\0';
	nova->num_casa = 0;
	nova->jogada_primaria_partida = &nova;
	nova->proxima_jogada = NULL;
	
	return nova;
} /*retorna um ponteiro p/ o item da proxima jogada*/

JOGADA *cria_partida(JOGADA **jogada_primaria){
	JOGADA *nova; /* declara um ponteiro p/ uma strutura do "TIPO: JOGADA" com "NOME: nova"*/
	nova = (JOGADA*) malloc(sizeof(JOGADA)); /*aloca espaco p/ um item (estrutra) do tipo JOGADA, e retorna o endereco p/ nova*/
	if(!nova) return NULL; /*testa se foi possivel alocar*/
	
	nova->autor = '\0';
	int t;
	for(t=0; t<(N-1); t++) nova->tabuleiro[t] = '_';
	nova->num_casa = 0;
	nova->jogada_primaria_partida = jogada_primaria;
	nova->proxima_jogada = NULL;
	
	return nova;
} /*retorna um ponteiro p/ o item da proxima jogada*/

JOGADA *insere_item_jogada(JOGADA *anterior){
	JOGADA *nova; /* declara um ponteiro p/ uma strutura do "TIPO: JOGADA" com "NOME: nova"*/
	nova = (JOGADA*) malloc(sizeof(JOGADA)); /*aloca espaco p/ um item (estrutra) do tipo JOGADA, e retorna o endereco p/ nova*/
	if(!nova) return NULL; /*testa se foi possivel alocar*/
	
	/*inicializa os objetos do novo item da lista de jogadas*/
	nova->autor = '\0';
	strcpy(nova->tabuleiro, anterior->tabuleiro); /*copia o tabuleiro anterior p/ o do novo item*/
	nova->num_casa = 0;
	nova->jogada_primaria_partida = anterior->jogada_primaria_partida; /*recebe um ponteiro que aponta p/ o primeiro item da lista*/
	nova->proxima_jogada = NULL; /*neste momento, este eh o ultimo item da lista, entao aponta p/ NULL*/
	
	return nova;
} /*adiciona um novo item (no final) na lista*/

PARTIDA *insere_item_lista(PARTIDA **cabeca){
	PARTIDA *nova; /* declara um ponteiro p/ um "TIPO PARTIDA" com "NOME nova" */
	nova = (PARTIDA*) malloc(sizeof(PARTIDA)); /* aloca espaco p/ um item do tipo PARTIDA, e retorna o endereço p/ "nova" */
	if(!nova) return NULL; /*se nao for possivel alocar espaco p/ o item*/
	
	/*inicializa os ponteiros*/
	nova->cabeca_partida = NULL;
	nova->lider = cabeca; /*aponta p/ a cabeca da lista*/
	nova->proxima_partida = NULL;
	
	return nova; /*retorna um ponteiro p/ o primeiro item da lista, em que um dos objetos eh um ponteiro para a lista do tipo JOGADA*/
}

int apaga_partida(JOGADA *primeira_jogada_apaga){
	int retorno;
	retorno = 0;
	if(!primeira_jogada_apaga->proxima_jogada) return 0; /*base: se o proximo item apontar p/ NULL, chegou ao fim da lista*/
	retorno = apaga_partida(primeira_jogada_apaga->proxima_jogada); /*chama funcao recursivamente, passando o endereco do proximo item*/
	free(primeira_jogada_apaga); /*libera o espaco do atual item*/
	return retorno; /*retorna ZERO de houve sucesso*/
} /*apaga uma lista de jogadas (partida)*/
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- FUNCOES DE MANIPULACAO DIRETA DAS LISTAS _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */


int verifica_vitoria(char iniciante, char tabuleiro[]){
	char maquina_comp, humano_comp;
	if(iniciante == 'H'){
 		humano_comp = 'X';
 		maquina_comp = 'O';
 	}
 	else{
 		humano_comp = 'O';
 		maquina_comp = 'X';
 	}
	
	/*vitoria do humano*/
	if((humano_comp == tabuleiro[0]) && (humano_comp == tabuleiro[1]) && (humano_comp == tabuleiro[2])) return 1; /*primeira linha do tabuleiro tem pecas iguais*/
	else if((humano_comp == tabuleiro[3]) && (humano_comp == tabuleiro[4]) && (humano_comp == tabuleiro[5])) return 1; /*segunda linha do tabuleiro tem pecas iguais*/
	else if((humano_comp == tabuleiro[6]) && (humano_comp == tabuleiro[7]) && (humano_comp == tabuleiro[8])) return 1; /*terceira linha do tabuleiro tem pecas iguais*/
	else if((humano_comp == tabuleiro[0]) && (humano_comp == tabuleiro[3]) && (humano_comp == tabuleiro[6])) return 1; /*primeira coluna do tabuleiro tem pecas iguais*/
	else if((humano_comp == tabuleiro[1]) && (humano_comp == tabuleiro[4]) && (humano_comp == tabuleiro[7])) return 1; /*segunda coluna do tabuleiro tem pecas iguais*/
	else if((humano_comp == tabuleiro[2]) && (humano_comp == tabuleiro[5]) && (humano_comp == tabuleiro[8])) return 1; /*terceira coluna do tabuleiro tem pecas iguais*/
	else if((humano_comp == tabuleiro[0]) && (humano_comp == tabuleiro[4]) && (humano_comp == tabuleiro[8])) return 1; /*diagonal principal com pecas iguais*/
	else if((humano_comp == tabuleiro[2]) && (humano_comp == tabuleiro[4]) && (humano_comp == tabuleiro[6])) return 1; /*diagonal secundaria com pecas iguais*/
	
	/*vitoria da maquina*/
	else if((maquina_comp == tabuleiro[0]) && (maquina_comp == tabuleiro[1]) && (maquina_comp == tabuleiro[2])) return -1; /*primeira linha do tabuleiro tem pecas iguais*/
	else if((maquina_comp == tabuleiro[3]) && (maquina_comp == tabuleiro[4]) && (maquina_comp == tabuleiro[5])) return -1; /*segunda linha do tabuleiro tem pecas iguais*/
	else if((maquina_comp == tabuleiro[6]) && (maquina_comp == tabuleiro[7]) && (maquina_comp == tabuleiro[8])) return -1; /*terceira linha do tabuleiro tem pecas iguais*/
	else if((maquina_comp == tabuleiro[0]) && (maquina_comp == tabuleiro[3]) && (maquina_comp == tabuleiro[6])) return -1; /*primeira coluna do tabuleiro tem pecas iguais*/
	else if((maquina_comp == tabuleiro[1]) && (maquina_comp == tabuleiro[4]) && (maquina_comp == tabuleiro[7])) return -1; /*segunda coluna do tabuleiro tem pecas iguais*/
	else if((maquina_comp == tabuleiro[2]) && (maquina_comp == tabuleiro[5]) && (maquina_comp == tabuleiro[8])) return -1; /*terceira coluna do tabuleiro tem pecas iguais*/
	else if((maquina_comp == tabuleiro[0]) && (maquina_comp == tabuleiro[4]) && (maquina_comp == tabuleiro[8])) return -1; /*diagonal principal com pecas iguais*/
	else if((maquina_comp == tabuleiro[2]) && (maquina_comp == tabuleiro[4]) && (maquina_comp == tabuleiro[6])) return -1; /*diagonal secundaria com pecas iguais*/
	
	else return 0; /*se deu velha retorna ZERO*/
	
} /*se existe tabuleiro de vitoria retorna verdadeiro, senao, retorna falso*/

int casas_ocupadas(char campo_jogo[]){
	int num, i, tam;
	num=0;
	tam = strlen(campo_jogo);
	for(i=0; i<tam; i++){
		if((campo_jogo[i] == 'X') || (campo_jogo[i] == 'O')) num++;
	}
	return num;
}

char *troca_marcadores(char tabuleiro_trocado[]){
	int i;
	for(i=0; i<(N-2); i++){
		if(tabuleiro_trocado[i] == 'X'){
			tabuleiro_trocado[i] = 'O';
			continue;
		}
		else if(tabuleiro_trocado[i] == 'O'){
			tabuleiro_trocado[i] = 'X';
		}
	}
	return tabuleiro_trocado;
}

int compara_jogadas(PARTIDA *cabeca_partida, char provavel_saida[]){
	int ordem_jogada; /*numero de casas ocupadas*/
	PARTIDA *partida_auxiliar;
	JOGADA *jogada_auxiliar;
	
	ordem_jogada = casas_ocupadas(provavel_saida); /*define o numero de posicoes ocupadas no tabuleiro da provavel jogada*/
	partida_auxiliar = cabeca_partida; /*endereco do primeiro item da lista de partidas (tipo PARTIDA)*/
	jogada_auxiliar = partida_auxiliar->cabeca_partida; /*ponteiro auxiliar pega endereco do primeiro item da lista de jogadas (tipo JOGADA)*/
	
	while(partida_auxiliar != NULL){ /*quando o ponteiro auxiliar (tipo PARTIDA) apontar p/ NULL, sai lo laco*/
		while((jogada_auxiliar->num_casa) < ordem_jogada){
			if(!jogada_auxiliar->proxima_jogada){
				goto pula_comparacao; /*se algum item apontar p/ NULL antes de chegar na jogada da ordem desejada, vai p/ proxima partida*/
			}
			jogada_auxiliar = jogada_auxiliar->proxima_jogada; /*pega o endereco do proximo item da "partida" (lista de itens do tipo JOGADA)*/
		} /*enquanto nao chegar na jogada (tabuleiro) compativel, com uma jogada de mesma ordem (mesmo numero de casas ocupadas)*/
		
		/*considerando que quem sai jogando marca 'X', o marcador usado por cada especie pode variar nas partidas*/
		char *tabuleiro_comparacao; /*ponteiro p/ um tabuleiro de comparacao, caso seja necessario trocar os marcadores*/
		if(jogada_auxiliar->autor == 'H'){
			tabuleiro_comparacao = troca_marcadores(jogada_auxiliar->tabuleiro); /*funcao que troca os marcadores*/
			if(!strcmp(provavel_saida, tabuleiro_comparacao)){
				return 0; /*se achar alguma jogada igual, entao a candidata nao eh adequada*/
			}
		} /*se foi a maquina que iniciou partida (da qual uma das jogadas esta sendo comparada) entao troca os marcadores*/
		else{
			if(!strcmp(provavel_saida, jogada_auxiliar->tabuleiro)){
				return 0; /*se achar alguma jogada igual, entao a candidata nao eh adequada*/
			}
		} /*se foi o humano, compara com a jogada que consta na estrutura*/
		
		pula_comparacao: /*goto" usado para nao fazer a comparacao dos tabuleiros de ordem diferente, mesmo nao havendo risco de serem considerados iguais*/
		
		/*atualiza ponteiros auxiliares*/
		partida_auxiliar = partida_auxiliar->proxima_partida; /*ponteiro auxiliar que aponta p/ o item da lista de partidas (tipo PARTIDA) pega o endereco do proximo item*/
		if(partida_auxiliar == NULL) break; /*se o ponteiro auxiliar apontar p/ NULL sai do laco*/
		jogada_auxiliar = partida_auxiliar->cabeca_partida; /*pega o endereco do primeiro item da outra "partida" (lista)*/
	} /*laco p/ percorrer a estrutura*/
	
	return 1; /*se chegou ate aqui, entao a jogada eh adequada*/
} /*funcao que recebe o tabuleiro do usuario e ponteiro p/ cabeca da estrutura, LOCALIZA os devidos itens na estrutura p/ comparar com a provavel jogada*/

void jogada_maquina(PARTIDA **cabeca_partidas, jogador *jogador_maquina, JOGADA *jogada_partida, int indice_jogadas){
	jogada_partida->autor = jogador_maquina->especie; /*define a especie do autor da jogada, maquina*/
	
	jogada_partida->num_casa = indice_jogadas; /*define o numero de casas ocupas/ordem da jogada pelo indice de jogadas*/
	jogada_partida->tabuleiro[N-1] = '\0';
	jogada_partida->tabuleiro[N-2] = '\0'; /*coloca o terminador nulo nas ultimas posicoes da string, p/ evitar o quebra-linha*/
	
	int k , adequado;
	adequado = 0;
	for(k=0; k<(N-2); k++){
		if(jogada_partida->tabuleiro[k] != '_') continue; /*se a posicao nao estiver livre, continua*/
		jogada_partida->tabuleiro[k] = jogador_maquina->marcador; /*preenche a casa livre*/
		if(compara_jogadas(*cabeca_partidas, jogada_partida->tabuleiro)){
			printf("M: %s\n", jogada_partida->tabuleiro); /*imprime jogada mais adequada*/
			++adequado;
			break; /*se retornou NAO-ZERO, jogada eh adequada*/
		}
		jogada_partida->tabuleiro[k] = '_'; /*apaga marcacao*/
	}
	
	if(!adequado){
		for(k=0; k<(N-2); k++){
			if(jogada_partida->tabuleiro[k] == '_') jogada_partida->tabuleiro[k] = 'O'; /*preenche a primeira posicao livre que encontrar*/
		}
		printf("M: %s  (Sem chance de NÃO perder!)\n", jogada_partida->tabuleiro);/*teste*/
	}/*se executou todos os loops e nenhuma jogada foi considerada adequada (nao incrementou "marcador de adequacao"), que evite uma derrota eminente, entao nao existe chance de NAO perder*/
}

void recebe_jogada_humano(jogador *jogador_humano, JOGADA *jogada_partida, int indice_jogadas){
	jogada_partida->autor = jogador_humano->especie; /*define a especie do autor da jogada (humano)*/
	printf("H: ");
	fgets(jogada_partida->tabuleiro, N, stdin); /*recebe e (sobrescreve) a configuracao do tabuleiro do humano (usuario)*/
	jogada_partida->tabuleiro[N-2] = '\0'; /*quebra-linha entra na penultima posicao da string*/
	jogada_partida->num_casa = indice_jogadas;
}


int realiza_movimento(PARTIDA **cabeca_partidas, jogador *primeiro, jogador *segundo, JOGADA *lista_mov, int indice){
	if(indice >= N) return 1; /*BASE 1: significa que ja prencheu as nove casas do tabuleiro, e deu velha*/
	
	if((indice % 2) != 0){ /*jogada impar, entao eh a vez de quem saiu jogando (primeiro)*/
		if(primeiro->especie == 'H') recebe_jogada_humano(primeiro, lista_mov, indice);
		else jogada_maquina(cabeca_partidas, primeiro, lista_mov, indice);
	}
	else{ /*se o resto de divisao por dois nao eh diferente de zero entao eh igual, e a jogada eh par*/
		if(segundo->especie == 'H') recebe_jogada_humano(segundo, lista_mov, indice);
		else jogada_maquina(cabeca_partidas, segundo, lista_mov, indice);
	}
	
	if(lista_mov->num_casa >= 5){ /*so pode haver vitoria depois de CINCO jogadas*/
		int vitoria;
		JOGADA **intermediario;
		intermediario = lista_mov->jogada_primaria_partida;
		
		vitoria = verifica_vitoria((*intermediario)->autor, lista_mov->tabuleiro); /*retorna "-1" se vitoria da maquina, "1" em vitoria do usuario e "0" se der velha*/
		if(vitoria) return vitoria;  /*chama funcao que verifica se ja tem tabuleiro de vitoria*/
	} /*BASE 2: tabuleiro de vitoria foi gerado, pela maquina ou humano*/

	lista_mov->proxima_jogada = insere_item_jogada(lista_mov); /*insere novo item (no final) na lista*/
	
	return realiza_movimento(cabeca_partidas, primeiro, segundo, lista_mov->proxima_jogada, indice + 1); /*recursividade: passa endereco do proximo item, incrementa a ordem da jogada*/
} /*se for a vez do computador decide a jogada, se nao recebe do usuario*/


void ordem_jogadas_user(jogador *primeiro, jogador *segundo){
	int inicial; /*quem faz primeira jogada, entrada do usuario*/
	printf("Quem joga primeiro? (digite 1 para humano ou 2 para maquina): ");
	scanf("%d", &inicial);
	getchar(); /*limpa o buffer*/
	
	if(inicial == 1){ /*se usuario entrou com "1", quer comecar jogando, entao o primeiro a jogar (usuario) eh identificado por 'H' e marca 'X' no tabuleiro*/
		primeiro->especie = 'H';
		primeiro->marcador = 'X';
		segundo->especie = 'M';
		segundo->marcador = 'O';
	}
	else{ /*se usuario entrou com "2", quer ser segundo a jogar, entao primeiro a jogar (maquina) eh identificado por 'M' e marca 'X' no tabuleiro, usuario marca 'O'*/
		primeiro->especie = 'M';
		primeiro->marcador = 'X';
		segundo->especie = 'H';
		segundo->marcador = 'O';
	}
}

void guarda_arquivo(JOGADA *jogada_arq){ /*recebe a primeira partida*/
	char arquivo[] = "derrotas.dat"; /*arquivo guarda as derrotas, fica no mesmo diretorio do codigo*/
	FILE *fp; /*ponteiro com o endereco de memoria do arquivo*/
	
	fp = fopen(arquivo, "a"); /*abre arquivo em modo de gravacao, se ele ja existe, adiciona conteudo ao fim do arquivo*/
	
	if(!fp){
		printf("Erro na abertura do arquivo."); /*função fopen() retorna um ponteiro NULL se houve erro ao abrir arquivo*/
		exit(2);
	}
	
	
	fprintf(fp, "%c\n", jogada_arq->autor); /*imprime (no arquivo) a especie de quem comecou a partida*/
	
	while(jogada_arq){
		jogada_arq->tabuleiro[N-1] = '\0'; /*coloca o terminador na penultima posicao, p/ evitar o quebra-linha*/
		fprintf(fp, "%s\n", jogada_arq->tabuleiro); /*imprime (no arquivo) o tabuleiro e pega o endereco do proximo item*/
		jogada_arq = jogada_arq->proxima_jogada; /*pega o endereco da proxima jogada*/
	} /*enquanto nao apontar p/ NULL (chegar ao fim da lista) continua escrevendo  os tabuleiros no arquivo*/
	fprintf(fp, "\n");
	
	fclose(fp); /*fecha o arquivo*/
}

int procura_char(char string[], char caracter){
	int tamanho, i;
	tamanho = strlen(string);
	for(i=0; i<tamanho; i++){
		if(string[i] == caracter) return 1; /*se ACHAR o caracter, retorna NAO-ZERO*/
	}
	return 0; /*se NAO ACHAR o caracter, retorna ZERO*/
} /*procura um caracter na "string"*/

void ordem_jogadas_arq(jogador *primeiro, jogador *segundo, char primespecie){
	if(primespecie == 'H'){ /*primeira jogada feita por humano, 'H' jogadas impares e 'M' jogadas pares*/
		primeiro->especie = primespecie;
		primeiro->marcador = 'X';
		segundo->especie = 'M';
		segundo->marcador = 'O';
	}
	else{ /*primeira jogada feita pela maquina, 'M' jogadas impares e 'H' jogadas pares*/
		primeiro->especie = 'M';
		primeiro->marcador = 'X';
		segundo->especie = 'H';
		segundo->marcador = 'O';
	}
} /*define a vez (jogada 'par' ou 'impar') de cada jogador ('H' ou 'M')*/

PARTIDA *pega_arquivo(){
	char arquivo[] = "derrotas.dat"; /*nome do arquivo que esta no mesmo diretorio deste codigo*/
	FILE *fp; /*ponteiro que recebe o endereco de memorio do arquivo*/
	
	fp = fopen(arquivo, "r"); /*abre o arquivo texto em modo (APENAS) leitura, o arquivo DEVE existir*/
	
	if(!fp){
		printf("Erro na abertura do arquivo."); /*fopen() retorna um ponteiro NULL se houve erro ao abrir arquivo*/
		return NULL;
	}


	PARTIDA *cabeca_lista; /*ponteiro (cabeca da lista) para um struct do tipo PARTIDA, sera o retorno da foncao e vai conter o endereco do primeiro item*/	
	PARTIDA **plista; /*ponteiro auxiliar*/
	plista = &cabeca_lista; /*coloca o endereco da cabeca "lista de partidas" (que eh um ponteiro que aponta p/ o primeiro item da lista) no ponteiro auxiliar*/
	JOGADA **pjogada; /*ponteiro auxiliar*/
	
	jogador primeiro_impar, segundo_par; /*estruturas com a especie ('H' ou 'M') e marcador de cada jogador ('X' ou 'O') p/ cada jogada (jogada par ou impar)*/
	
	int contador_casas_ocupadas; /*contador de casas ocupadas no tabuleiro*/
	char vetor_auxiliar[N]; /*vetor onde sera colocado o conteudo da linha que fgets() pega do arquivo*/
	
	while(!feof(fp)){
		/*em TODAS as linhas existem no maximo nove caracteres + quebra-linha, fgets() lê no maximo N caracteres ou ate o quebra-linha*/
		fgets(vetor_auxiliar, N, fp); /*fgets() pega o conteudo de uma linha do arquivo apontado por fp e coloca no vetor auxiliar*/
		vetor_auxiliar[N-2] = 0; /*zera a posicao do quebra-linha*/
		
		if(procura_char(vetor_auxiliar, 'X') || procura_char(vetor_auxiliar, 'O') || procura_char(vetor_auxiliar, '_')){
			strcpy((*pjogada)->tabuleiro, vetor_auxiliar);
			(*pjogada)->num_casa = ++contador_casas_ocupadas; /*casas ocupadas no tabuleiro*/
			
			if((contador_casas_ocupadas % 2) != 0){
				(*pjogada)->autor = primeiro_impar.especie; /*jogada impar*/
			}
			else (*pjogada)->autor = segundo_par.especie; /*jogada par*/
			
			(*pjogada)->proxima_jogada = insere_item_jogada(*pjogada); /*insere mais um item na lista de jogadas*/
			pjogada = &((*pjogada)->proxima_jogada); /*faz o ponteiro auxiliar apontar p/ o proximo item da lista de jogadas*/
			continue;
		} /*linha representa uma jogada*/
		else if(procura_char(vetor_auxiliar, 'H') || procura_char(vetor_auxiliar, 'M')){
			
			*plista = insere_item_lista(plista); /*insere um item na lista de partidas (tipo PARTIDA), e passa o endereco da cabeca da lista*/
			pjogada = &((*plista)->cabeca_partida); /*ponteiro auxiliar de jogadas (tipo JOGADA) recebe o endereco DO ITEM QUE APONTA P/ a primeira jogada da partida*/
			*pjogada = cria_partida(pjogada); /*coloca o endereco do primeiro item da lista de jogadas (tipo JOGADA) no objeto (cabeca da lista) que aponta p/ a primeira jogada*/
			(*plista)->cabeca_partida->autor = vetor_auxiliar[0]; /*define o autor da primeira jogada*/
			ordem_jogadas_arq(&primeiro_impar, &segundo_par, (*plista)->cabeca_partida->autor); /*define a ordem de quem joga quando*/
			contador_casas_ocupadas = 0; /*inicializa o contador de casas ocupadas*/
			
			continue;
		} /*linha do inciante, quem saiu jogando, que eh onde comeca uma partida*/
		else{
			(*pjogada)->proxima_jogada = NULL; /*faz o objeto "proxima jogada" do ultimo item da lista (JOGADA) apontar p/ NULL*/
			plista = &((*plista)->proxima_partida); /*ponteiro auxiliar (PARTIDA) pega o endereco do proximo item (que neste momento, aponta NULL)*/
		} /*entao eh uma linha vazia*/
	}
	
	fclose(fp);
	return cabeca_lista; /*retorna um ponteiro para a cabeca da lista em que cada item tem um objeto que aponta p/ uma lista de jogadas (partida)*/
}
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ OUTRAS FUNCOES _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ */


int main(){
	
	PARTIDA *cabeca_estrutura; /*ponteiro p/ a cabeca da estrutura de dados com as jogadas que ja estao no 'derrotas.dat'*/
 	cabeca_estrutura = pega_arquivo();
 	if(!cabeca_estrutura){
 		printf("'derrotas.dat' não existe!\nPrograma encerrado.\n");
 		exit(0);
 	}
	
	
	struct jogador primeiro_main, segundo_main; /* declara duas estruturas do "TIPO jogador" com "NOMES primeiro e segundo" */
	ordem_jogadas_user(&primeiro_main, &segundo_main); /*define quem realiza movimento nas jogadas impar e par*/
	
	JOGADA *primeira_jogada_main; /*cabeca da lista de jogadas, da partida que o "aprendiz" vai jogar*/
	
 	primeira_jogada_main = cria_partida_jogada();
	
	int indice_jogadas, /*indice da jogada, para saber se eh uma jogada impar ou par*/
		retorno_movimento; /*recebe ZERO se der velha, MENOS-UM se maquina ganhar, UM se humano ganhar*/
	indice_jogadas = 1;
	
	retorno_movimento = realiza_movimento(&cabeca_estrutura, &primeiro_main, &segundo_main, primeira_jogada_main, indice_jogadas);
	
	if(retorno_movimento == 1){
		guarda_arquivo(primeira_jogada_main); /*guarda no arquivo*/
	}
}