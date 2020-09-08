/*Segundo Trabalho de Algoritmos e Estrutura de Dados II*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lista.h"

typedef lista fila;/*Definindo lista como uma fila*/

/*Variaveis Globais*/
int tempo;

/*Declaração de Funções*/

/*transfere um no de uma fila para outra*/
no *transfere_no(no* trans,fila *origem,fila *destino);

/*Lê todos os dados do arquivo de entrada e escreve na fila de 'carros'*/
int leia_arquivo(char fp[], fila *f);

/*Escreve os dados no arquivo de saida*/
void escreve_arquivo(no *n,char operacao[]);

/*retorna o endereço do nó preferencial*/
no *compara_preferencial(no *primeiro,no *segundo);

/*Faz o carro mais prioritario de uma fila se tornar o primeiro*/
no *organiza(fila *f);

/*retorna o numero de pedidos, e torna o prioritário o primeiro da fila, adiciona novos pedidos*/
int atualiza_pedidos(fila *pedidos,fila *carros);

/*retorna 1 se alguem ja montou e 0 se não, torna o prioritário o primeiro da fila de montagem*/
int atualiza_montagem(fila *montagem);

/*retorno 1 se tem espaço na pintura e 0 se não*/
int atualiza_pintura(int tempo_pintura);

/*Manda o prioritario para frente, retorna o espaço no patio*/
int atualiza_patio(fila *patio);

/*---------------------Programa Principal--------------------------*/
void main(int argc,char *argv[])
{
	FILE *arquivo;
	int num_car,num_pedidos,tempo_pintura;
	int esp_pintura,esp_patio,term_mont,carro_pint;/*carro_pint serve para ter controle no tempo de pintura*/
	fila *pedidos,*patio,*montagem,*carros;
	no *pref;/*Guarda o endereço do carro preferencial que irá para a pintura*/
	if (argc!=2)/*Teste se o usuario passou os parametros certos*/
    {
        printf("Você não informou o nome do arquivo!\n");
        exit(1);
    }
    if ((arquivo=fopen(argv[1],"a+"))==NULL)/*Teste se o arquivo foi aberto corretamente*/
    {
        printf("Não foi possivel criar arquivo!\n");
        exit(1);
    }
    fclose(arquivo);
    /*
        RESUMO DO QUE OCORRE DENTRO DO WHILE:
        --------------------------------------
        Enquanto não acabar os carros continua
            atualiza o tempo
            atualiza a fila de pedidos
            atualiza o numero de carros que terminaram na linha de montagem
            atualiza o pátio(prioritário fica na frente)
            atualiza se algum carro ja terminou na pintura
            Se ha espaço na pintura
                verifico se ha algum carro no patio ou terminado na montagem
                    se sim
                        mando pintar
                        inicio o contador tempo de pintura
                    se não
                        digo para o sistema que não tem carro na pintura (carro_pint=0)
                    ignora os proximos if
            se eu tenho pedidos para fazer
				verifico se ha espaço na montagem
					se sim
						mando montar o preferencial
					se não
						mantenha na fila de espera para pedidos
            se algum carro ja montou
                se há espaço no pátio
                    mando pro patio os preferenciais
				ignora os proximos if
			
    */
    carros=cria_lista();/*Inicializa as filas*/
    pedidos=cria_lista();
    montagem=cria_lista();
    patio=cria_lista();
    num_car=leia_arquivo(argv[1],carros);/*Leio os dados*/
    tempo=-1;/*Inicializo contadores*/
    tempo_pintura=0;
    carro_pint=0;
	while(num_car-1)/*Enquanto eu tiver carros no sistema*/
	{
		tempo++;
		/*atualização dos dados do sistema*/
		num_pedidos=atualiza_pedidos(pedidos,carros);
		term_mont=atualiza_montagem(montagem);
		esp_patio=atualiza_patio(patio);
		if(carro_pint) {tempo_pintura--;}
		esp_pintura=atualiza_pintura(tempo_pintura);
		if(esp_pintura)/*Se a espaço na pintura*/
		{
			if(carro_pint)/*Se algum carro acabou de pintar*/
			{
				num_car--;
				carro_pint=0;
			}
			if(patio->tam)/*Se tem alguem no patio*/
			{
				if(term_mont)/*E alguem terminou na montagem*/
				{
					/*Manda pintar o preferencial*/
					pref=compara_preferencial(patio->primeiro,montagem->primeiro);
					pref->o.tempo_processo=tempo;
					/*Veja quem é preferencial e manda para saida*/
					if(pref==patio->primeiro)
					{
						escreve_arquivo(patio->primeiro,"PINTAR");
						destruir_no(patio->primeiro,patio);
					}
					else
						escreve_arquivo(montagem->primeiro,"PINTAR");
						destruir_no(montagem->primeiro,montagem);
				}
				/*Se ninguem terminou na montagem manda o primeiro carro do patio*/
				else
				{
					escreve_arquivo(patio->primeiro,"PINTAR");
					destruir_no(patio->primeiro,patio);
				}
				/*Inicializa a pintura*/
				tempo_pintura=5;
				carro_pint=1;
				continue;
			}
			/*Se não tem ninguem no patio, mais um carro ja terminou de pintar*/
			if(term_mont)
			{
				/*Manda o primeiro carro da montagem para pintura*/
				escreve_arquivo(montagem->primeiro,"PINTAR");
				destruir_no(montagem->primeiro,montagem);
				/*Inicializa a pintura*/
				tempo_pintura=5;
				carro_pint=1;
				continue;
			}
		}
		if(num_pedidos)/*Se há algum pedido de carro a fazer*/
		{
			if(montagem->tam<3)/*se a lugar na montagem*/
			{
				/*manda o primeiro da lista de pedidos para a montagem*/
				pedidos->primeiro->o.tempo_atraso=0;
				pedidos->primeiro->o.tempo_processo=tempo;/*inicializa o processo*/
				escreve_arquivo(pedidos->primeiro,"MONTAR");
				transfere_no(pedidos->primeiro,pedidos,montagem);
				continue;
			}
		}
		if(term_mont)
		{
			if(esp_patio)/*Se alguem ja terminou de montar e há espaço no patio*/
			{
                /*manda pro patio*/
                montagem->primeiro->o.tempo_atraso=0;
                montagem->primeiro->o.tempo_processo=tempo;
                escreve_arquivo(montagem->primeiro,"PATIO");
                transfere_no(montagem->primeiro,montagem,patio);
                continue;
			}
		}
	}
	/*Destruir as listas*/
	destruir_lista(carros);
	destruir_lista(pedidos);
	destruir_lista(montagem);
	destruir_lista(patio);
}

/*--------------------Implementação das funções--------------------------------------*/

int leia_arquivo(char arquivo[],lista *carros){
	FILE *fp;
	int p;
	fp=fopen(arquivo,"r");
	no *aux;/*ponteiro auxiliar*/
	objeto o;
	/*Leia a primeira linha fora do while*/
	fscanf(fp,"%d %d %c %s\n",&o.tempo_pedido,&o.tempo_montagem,&o.carroceria,o.modelo);
	carros->primeiro=inserir_dados(o,carros);
	/*Leia todas as linhas até o final do documento*/
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %c %s\n",&o.tempo_pedido,&o.tempo_montagem,&o.carroceria,o.modelo);
		carros->primeiro=inserir_dados(o,carros);
	}
	fclose(fp);
	return carros->tam; /*retorna o numero total de carros a serem montados*/
}

void escreve_arquivo(no *n,char operacao[])
{
	FILE *fp;
	fp = fopen("teste.out", "a"); /*abre arquivo de texto APENAS p/ gravacao em modo "append"*/
	/*Escreve no documento de saida, a operação, o tempo que foi executado o processo, e a carroceria*/
	fprintf(fp, "%s %d %c\n", operacao,tempo,n->o.carroceria);
	fclose(fp);
}

/*retorna o endereço do nó preferencial(por padrã, manda o primeiro)*/
no *compara_preferencial(no *primeiro,no *segundo)
{
    /*Para o caso de atualiza_montagem estar chamando, pergunda se o carro já terminou de montar*/
    if(primeiro->o.tempo_atraso>=0)
	{
		if(segundo->o.tempo_atraso>=0)
		{
			/*Definindo como 10 min o maximo que um carro pode sofrer de atraso toleravel*/
			if(!strcmp(primeiro->o.modelo,"OXX"))/*Se primeiro é modelo prioritario*/
			{
				if(!strcmp(segundo->o.modelo,"OXX"))/*Se segundo é modelo prioritario*/
				{
					if(primeiro->o.tempo_atraso>=segundo->o.tempo_atraso)/*Verifica quem esta mais atrasado*/
						return primeiro;
					return segundo;
				}
				/*Se o segundo esta a mais de 10 min atraso, e mais atrasado que primeiro, é preferencial*/
				if((segundo->o.tempo_atraso>10)&&(segundo->o.tempo_atraso>primeiro->o.tempo_atraso))
					return segundo;
				return primeiro;
			}
			else if(!strcmp(segundo->o.modelo,"OXX"))/*Se só o segundo é modelo prioritario*/
			{
				/*Verifica se o primeiro esta a mais de 10 min atrasado, e mais atrasado que o segundo*/
				if((primeiro->o.tempo_atraso>10)&&(primeiro->o.tempo_atraso>segundo->o.tempo_atraso))
					return primeiro;
				return segundo;
			}
			else/*Nenhum dos dois é modelo prioritario*/
			{
				/*O mais atrasado é o prioritario*/
				if(primeiro->o.tempo_atraso>=segundo->o.tempo_atraso)
					return primeiro;
				return segundo;
			}
		}
		return primeiro;
	}
	if(segundo->o.tempo_atraso>=0)/*Só o segundo terminou de montar*/
		return segundo;
	return primeiro;
}

no *transfere_no(no* trans,fila *origem,fila *destino)/*transfere um nó de uma fila para outra*/
{
	remover_no(trans,origem);
	inserir_no(trans,destino);
}

no *organiza(fila *f)/*Descobre o prioritário, e torna-o o primeiro*/
{
	no *mais_pref, *aux;
	mais_pref=f->primeiro;
	aux=f->primeiro;
	if(!aux) return NULL;
	while(aux->sucessor)/*procura prioritário*/
	{
		mais_pref=compara_preferencial(mais_pref,aux->sucessor);
		aux=aux->sucessor;
	}
	if(mais_pref!=f->primeiro)/*Se for diferente do primeiro, passa a ser o primeiro*/
	{	
		mais_pref=remover_no(mais_pref,f);
		inserir_no_inicio(mais_pref,f);
	}
	return f->primeiro=mais_pref;
}

int atualiza_patio(fila *patio)
{
    no *aux;
    aux=patio->primeiro;
    while(aux)/*Atualiza o tempo de atraso no patio*/
    {
        aux->o.tempo_atraso=tempo-aux->o.tempo_processo;/*tempo atual - tempo de chegada no pátio*/
        aux=aux->sucessor;
    }
    patio->primeiro=organiza(patio);/*Torna o prioritário o primeiro*/
    return (5-patio->tam);/*espaço no pátio*/
}

int atualiza_pedidos(fila *pedidos,fila *carros)
{
	no *aux1,*aux2;
	aux1=pedidos->primeiro;
	while(aux1)/*Se ficou atrasado*/
    {
        aux1->o.tempo_atraso++;
        aux1=aux1->sucessor;
    }
    aux1=carros->primeiro;
	while((aux1)&&(aux1->o.tempo_pedido==tempo))/*Caso receba um pedido para montagem de carro agora, manda para a fila de pedidos*/
	{
		aux1->o.tempo_atraso=0;
		aux2=aux1->sucessor;
		transfere_no(aux1,carros,pedidos);
		aux1=aux2;
	}
	pedidos->primeiro=organiza(pedidos);/*Torna o prioritário o primeiro*/
	return pedidos->tam;
}

int atualiza_montagem(fila *montagem)
{
	no *aux;
	int terminou=0;
	aux=montagem->primeiro;
	while(aux)/*atualiza o tempo de atraso*/
	{
		/*tempo atraso = tempo atual -(tempo de chegada + tempo de montagem)*/
		aux->o.tempo_atraso=tempo-(aux->o.tempo_processo+aux->o.tempo_montagem);
		if(aux->o.tempo_atraso>=0)/*caso esteja atrasado*/
			terminou=1;
		aux=aux->sucessor;
	}
	if(terminou)/*se alguem terminou, torna o prioritário o primeiro da fila*/
	{
		montagem->primeiro=organiza(montagem);
		return 1;
	}
	return 0;
}

int atualiza_pintura(int tempo_pintura)
{
	if(!tempo_pintura)
		return 1;
	return 0;
}
