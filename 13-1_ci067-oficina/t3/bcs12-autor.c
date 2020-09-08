#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#define MAX_TAM 10000 /*numero de caracteres p/ enunciados da questao e alternativa*/

int main(){

	char opcao_acao_geral;
	opcao_acao_geral = '$';
	
	PROVA cabeca_prova;
	cabeca_prova.numero_questoes = 0; /*inicializa o tamanho da prova*/
	cabeca_prova.primeira_questao = NULL; /*inicializa o ponteiro p/ primeira questao*/
	cabeca_prova.ultima_questao = NULL; /*inicializa o ponteiro p/ ultima questao*/
	int tamanho_nome_arquivo;
	
	
	printf("\nPara iniciar crie uma '(N)ova Prova' ou '(C)arregue questões de um arquivo'\n");
	while(opcao_acao_geral != 'S'){
		printf("Escolha uma opção:\n(C)arregar questões de um arquivo.\n(N)ova prova.\n(I)nserir questão.\n(R)emover questão.\n(G)uardar questões em arquivo.\n(S)air.\nEscolha uma atividade: ");
		opcao_acao_geral = toupper(getchar());
		getchar(); /*limpar o buffer*/
		
		if(opcao_acao_geral == 'N'){
			cabeca_prova.primeira_questao = adiciona_questao(); /*adiciona a primeira questao da prova*/
			if(!cabeca_prova.primeira_questao){ /*testa se alocou a primeira questao da nova prova*/
				printf("N$ Erro ao criar nova prova!\n");
				continue;
			}
			edita_enunciado_questao(cabeca_prova.primeira_questao); /*prenche o objeto "enunciado_questao" do item da lista do tipo QUESTAO*/
			char opcao_inserir_alternativa;
			opcao_inserir_alternativa = '$';
			
			ALTERNATIVA **auxiliar_alternativa; /*declaro um ponteiro auxiliar p/ outro ponteiro*/
			auxiliar_alternativa = &((cabeca_prova.primeira_questao)->conjunto_alternativas); /*ponteiro auxiliar aponta p/ o primeiro item da lista*/
			
			do{
				*auxiliar_alternativa = adiciona_alternativa(); /*aloca um item da lista de alternativas (tipo ALTERNATIVA) e atribui o endereco para onde o ponteiro auxiliar aponta"*/
				edita_alternativa(*auxiliar_alternativa); /*edita a alternativa, preenche o enunciado e a resposta*/
				*auxiliar_alternativa = (**auxiliar_alternativa).proxima_alternativa; /*atualiza o ponteiro auxiliar, "auxiliar_alternativa" aponta p/ o proximo item da lista*/
				
				printf("N$ (A)dicionar alternativa.\nN$ (S)air.\nN$ ");
				opcao_inserir_alternativa = toupper(getchar());
				getchar(); /*limpar o buffer*/
			} while(opcao_inserir_alternativa != 'S'); /*enquanto a condicao for verdade (nao quiser SAIR), adiciona alternativas*/
			
			cabeca_prova.ultima_questao = cabeca_prova.primeira_questao; /*lista tem apenas UM item*/
			(cabeca_prova.ultima_questao)->ordem = ++cabeca_prova.numero_questoes; /*incrementa o numero de questoes no header e numera a questao*/
		} /*nova prova*/
		
		else if(opcao_acao_geral == 'C'){
			char *arquivo; /*guarda o nome do arquivo que usuario entra*/
			arquivo = (char*) calloc(50, sizeof(char));
			printf("C$ Digite o nome do arquivo:\nC$ ");
			fgets(arquivo, 49, stdin); /*recebe a string com o nome do arquivo, pega ateh o "quebra-linha"*/
			
			tamanho_nome_arquivo = strlen(arquivo);
			arquivo[tamanho_nome_arquivo-1] = '\0'; /*tira o "quebra-linha" do nome do arquivo que vai ser aberto*/
			
			FILE *fp;
			fp = fopen(arquivo, "r"); /*abre arquivo APENAS em modo leitura*/
			
			if(!fp){
				printf("C$ Impossivel abrir arquivo!\n\n");
				continue;
			}
			
			char c; /*caracter intermediario*/
			int controle_ordem, tamanho_enunciado; /*"contador" que define a acao a ser feita*/
			controle_ordem = -1;
			
			ALTERNATIVA **paaux; /*ponteiro auxiliar para alternativas*/
			
			while(!feof(fp)){
				
				c = getc(fp); /*le caracter a caracter*/
				
				if(c == '{' || c == '}' || c == '|' || c == '@' || c == '#'){ /*caracter especial, define acao*/
					if(c == '{'){ /*enunciado da alternativa*/
						controle_ordem = 1;
						
						*paaux = adiciona_alternativa(); /*aloco espaco p/ uma alternativa*/
						(*paaux)->enunciado_alternativa = (char*) calloc(MAX_TAM, sizeof(char)); /*aloco espaco bem grande p/ o enunciado da alternativa*/
						
						continue;
					}
					else if(c == '|'){ /*resposta da alternativa*/
						controle_ordem = 2;

						continue;
					}
					else if(c == '}'){ /*fim da alternativa*/
						controle_ordem = -1;

						tamanho_enunciado = strlen((*paaux)->enunciado_alternativa); /*determina o tamanho que eh utilizado pelo enunciado da alternativa*/
						(*paaux)->enunciado_alternativa = (char*) realloc((*paaux)->enunciado_alternativa, tamanho_enunciado*sizeof(char)); /*realoca o enunciado da alternativa p/ tamanho real*/
						*paaux = (**paaux).proxima_alternativa; /*atualiza ponteiro auxiliar p/ proxima alternativa*/
						
						continue;
					}
					else if(c == '#'){ /*enunciado da questao*/
						if(controle_ordem == 3) continue; /*se ja estiver lendo o enunciado da questao, nao faz nada com caracter especial que "pula linha"*/
						controle_ordem = 3;
						
						if(!cabeca_prova.ultima_questao){ /*se estiver apontando p/ NULL, iniciando uma nova prova daqui, nao faz apontar p/ o seguinte*/
							cabeca_prova.ultima_questao = adiciona_questao(); /*adiciono o ultimo item da lista*/
							cabeca_prova.primeira_questao = cabeca_prova.ultima_questao; /*se nao foi criada "nova prova", a primeira questao ainda aponta p/ NULL*/
						}
						else{ /*se nao estiver apontando p/ NULL, ja tiver iniciado uma prova, ele de fato esta apontando p/ a ultima questao*/
							cabeca_prova.ultima_questao = (cabeca_prova.ultima_questao)->questao_seguinte; /*"ponteiro auxiliar" aponta p/ local que sera da ultima questao*/
							cabeca_prova.ultima_questao = adiciona_questao(); /*adiciono uma questao no ultimo item da lista*/
						}
						
						if(!cabeca_prova.ultima_questao){
							printf("Erro ao carregar questao de arquivo!\n\n"); /*testa se alocou a ultima (ateh agora) questao da prova*/
							break;
						}
						
						(cabeca_prova.ultima_questao)->enunciado_questao = (char*) calloc(MAX_TAM, sizeof(char)); /*aloco espaco (zerado) bem grande p/ o enunciado da questao*/
						(cabeca_prova.ultima_questao)->ordem = ++cabeca_prova.numero_questoes; /*incrementa o numero de questoes no header e numera a questao*/
						paaux = &((cabeca_prova.ultima_questao)->conjunto_alternativas); /*ponteiro auxiliar aponta p/ o primeiro item da lista de alternativas*/
						
						continue;
					}
					else if(c == '@'){ /*fim da questao*/
						controle_ordem = -1;

						tamanho_enunciado = strlen((cabeca_prova.ultima_questao)->enunciado_questao); /*verifica o tamanho utilizado pelo enunciado da questao*/
						tamanho_enunciado -= 2; /*subtrai as duas ultimas posicoes, contem "quebra-linha"*/
						(cabeca_prova.ultima_questao)->enunciado_questao = (char*) realloc((cabeca_prova.ultima_questao)->enunciado_questao, tamanho_enunciado*sizeof(char)); /*realoca o enunciado p/ tamanho real*/
						
						continue;
					}
				} /*caracter especial, define acao*/
				
				if(controle_ordem == 1) concatena_caracter_string((*paaux)->enunciado_alternativa, c); /*coloca um caracter no final do enunciado da alternativa, recebendo o enunciado da alternativa*/
				else if(controle_ordem == 2) (*paaux)->resposta = c; /*recebe a resposta da alternativa ('V' ou 'F')*/
				else if(controle_ordem == 3){ /*recebendo o enunciado da questao*/
					if(c == ' ' && (cabeca_prova.ultima_questao)->enunciado_questao[0] == '\0') continue; /*nao pega o espaco que separa o caracter especial do enunciado*/
					if(c == '\n') continue;
					concatena_caracter_string((cabeca_prova.ultima_questao)->enunciado_questao, c); /*coloca um caracter no final do enunciado da questao*/
				}
				else continue;
			}
			
			fclose(fp);
		}/*carregar arquivo*/
		
		else if(opcao_acao_geral == 'I'){
			char opcao_inserir_questao, opcao_inserir_alternativa; /*variaevis de condicao dos loop's*/
			opcao_inserir_questao = '$';
			opcao_inserir_alternativa = '$';
			
			QUESTAO *auxiliar_questao_anterior; /*ponteiro auxiliar p/ o item ANTERIOR, lista duplamente encadeada, usado apenas p/ fazer as ligacoes dos itens*/
			/*p/ o "tipo QUESTAO" o ponteiro auxiliar sera o item do header que SEMPRE aponta p/ o ultimo item da lista*/
			auxiliar_questao_anterior = cabeca_prova.ultima_questao; /*neste momento aponta p/ o ultimo item (de fato) que logo sera o penultimo*/
			cabeca_prova.ultima_questao = (cabeca_prova.ultima_questao)->questao_seguinte; /*atualiza ponteiro, agora, aponta p/ NULL*/
			cabeca_prova.ultima_questao = adiciona_questao(); /*aloco espaco p/ um item "tipo QUESTAO"*/
			
			ALTERNATIVA *alternativa_auxiliar; /*ponteiros auxiliares*/
			alternativa_auxiliar = (cabeca_prova.ultima_questao)->conjunto_alternativas; /*inicializa ponteiro auxiliar "tipo ALTERNATIVA"*/
			
			do{
				edita_enunciado_questao(cabeca_prova.ultima_questao); /*chama funcao que edita esse item (tipo QUESTAO), recebe enunciado...*/
				(cabeca_prova.ultima_questao)->ordem = ++cabeca_prova.numero_questoes; /*incrementa o numero de questoes no header e numera a questao*/
				
				do{
					alternativa_auxiliar = adiciona_alternativa(); /*aloco espaco p/ um item "tipo ALTERNATIVA"*/
					edita_alternativa(alternativa_auxiliar); /*chama funcao que edita a alternativa, recebe o enunciado e resposta*/
					alternativa_auxiliar = alternativa_auxiliar->proxima_alternativa; /*atualiza o ponteiro auxiliar de alternativas*/
					
					printf("I$ (A)dicionar outra alternativa.\nI$ (S)air.\nI$ "); /*pergunta se quer adicionar mais uma alternativa*/
					opcao_inserir_alternativa = toupper(getchar());
					getchar(); /*limpar o buffer*/
				}while(opcao_inserir_alternativa != 'S');
				printf("I$ (A)dicionar nova questão.\nI$ (S)air.\nI$ "); /*pergunta se quer adicionar mais uma questao*/
				opcao_inserir_questao = toupper(getchar());
				getchar(); /*limpar o buffer*/
				if(opcao_inserir_questao == 'A'){ /*se for adicionar mais uma questao*/
					cabeca_prova.ultima_questao = (cabeca_prova.ultima_questao)->questao_seguinte; /*atualiza o ponteiro auxiliar, que eh o item do header q aponta p/ o ultimo*/
					cabeca_prova.ultima_questao = adiciona_questao(); /*aloco espaco p/ um item "tipo QUESTAO"*/
				}
			}while(opcao_inserir_questao != 'S');
		} /*inserir questao*/
		
		else if(opcao_acao_geral == 'R'){
			char opcao_remover_questao;
			opcao_remover_questao = '$';
			
			QUESTAO *pq, /*ponteiro auxiliar p/ percorrer a lista*/
				*pant; /*ponteiro auxiliar p/ guardar o item anterior*/
			pq = cabeca_prova.primeira_questao; /*aponta p/ o primeiro item da lista*/
			pant = cabeca_prova.primeira_questao; /*como nao tem nenhum item antes do primeiro, aponta p/ o primeiro*/
			
			while(pq){ /*enquanto nao apontar p/ NULL*/
				printf("R$ %d. %s\nR$ (R)emover.\nR$ (C)ontinuar.\nR$ ", pq->ordem, pq->enunciado_questao);
				opcao_remover_questao = toupper(getchar());
				getchar(); /*limpar o buffer*/
				if(opcao_remover_questao == 'R') remove_questao(pant); /*chama funcao que remove um noh da lista tipo QUESTAO*/
				pant = pq; /*pega sempre o item anterior a "pq"*/
				pq = pq->questao_seguinte; /*atualiza o ponteiro*/
			}
		} /*feita, testada, NAO-funcionando(totalmente)*/
		
		else if(opcao_acao_geral == 'G'){
			char *arquivo_saida;
			arquivo_saida = (char*) calloc(50, sizeof(char));
			printf("G$ Digite o nome do arquivo de saida: ");
			fgets(arquivo_saida, 49, stdin); /*recebe a string com o nome do arquivo*/
			tamanho_nome_arquivo = strlen(arquivo_saida);
			arquivo_saida[tamanho_nome_arquivo-1] = '\0'; /*tira o "quebra-linha"*/
			
			FILE *fp;
			fp = fopen(arquivo_saida, "w"); /*cria arquivo de texto APENAS p/ gravacao*/
			
			QUESTAO *questao_auxiliar;
			questao_auxiliar = cabeca_prova.primeira_questao; /*ponteiro auxiliar de questoes aponta p/ a primeira questao da lista*/
			ALTERNATIVA *alternativa_auxiliar;
			
			while(questao_auxiliar != NULL){
				fprintf(fp, "# %s\n#\n", questao_auxiliar->enunciado_questao); /*imprime enunciado da questao no arquivo*/
				alternativa_auxiliar = questao_auxiliar->conjunto_alternativas; /*atualiza ponteiro auxiliar p/ alternativas*/
				while(alternativa_auxiliar != NULL){
					printf("ok.2.\n");
					fprintf(fp, "{%s|%c}", alternativa_auxiliar->enunciado_alternativa, alternativa_auxiliar->resposta); /*imprime enunciado e resposta da alternativa*/
					alternativa_auxiliar = alternativa_auxiliar->proxima_alternativa; /*atualiza ponteiro auxiliar*/
				}
				fprintf(fp, "@\n\n"); /*coloca outros caracteres especiais*/
				questao_auxiliar = questao_auxiliar->questao_seguinte; /*atualiza ponteiro auxiliar*/
			}
			
			fclose(fp);
		} /*ERRO*/
	}/*fim_while*/
}
