/*Biblioteca para trabalhar com lista*/
#include<stdio.h>
#include<stdlib.h>

typedef struct objeto{
	char modelo[4];/*modelo de carro*/
	char carroceria;/*modelo de carroceria*/
	int tempo_pedido;/*Tempo em que é efetuado o pedido*/
	int tempo_montagem;/*tempo que demora a montagem*/
	int tempo_atraso;/*tempo que esta atrasado em determinado processo*/
	int tempo_processo;/*tempo que iniciou dado processo*/
}objeto;

typedef struct no{
	objeto o;
	struct no *antecessor;
	struct no *sucessor;
}no;

typedef struct{ /*"header" p/ uma lista de itens do tipo no*/
	no *primeiro; /*ponteiro p/ o primeiro elemento/item da lista*/
	no *ultimo; /*ponteiro p/ o ultimo elemento/item da lista*/
	int tam; /*tamanho da lista, numero de elementos que a lista possui*/
}lista;

/*Criar a lista*/
lista *cria_lista(void){
	lista *l=malloc(sizeof(lista));
	if(!l) return NULL;
	l->tam=0;
	l->primeiro=NULL;
	l->ultimo=NULL;
	return l;
}

/*Destruir a lista*/
void destruir_lista(lista *l){
	no *n=l->primeiro;
	while(n)
	{
		l->primeiro=n->sucessor;
		free(n);
	}
	free(l);
}

/*Inserir novos dados num nó não existente(função para trabalhar com fila)*/
no *inserir_dados(objeto o,lista *l){
	no *novo=malloc(sizeof(no));
	if(!novo) return NULL;
	novo->o=o;
	if(!l->primeiro){
		l->primeiro=novo;
	}
	else{
		l->ultimo->sucessor=novo;
	}
	novo->sucessor=NULL;
	novo->antecessor=l->ultimo;
	l->ultimo=novo;
	l->tam++;
	return l->primeiro;
}

/*Inserir um nó já existente numa lista(trabalha com filas)*/
no *inserir_no(no *n,lista *l){
	if(!n) return NULL;
	if(!l->primeiro){
		l->primeiro=n;
	}
	else{
		l->ultimo->sucessor=n;
	}
	n->sucessor=NULL;
	n->antecessor=l->ultimo;
	l->ultimo=n;
	l->tam++;
	return l->primeiro;
}

/*Idem anterior, mais para inserir no inicio*/
no *inserir_no_inicio(no *n,lista *l)
{
	if(!n) return NULL;
	if(!l->primeiro)
		l->ultimo=n;
	else
		l->primeiro->antecessor=n;
	n->antecessor=NULL;
	n->sucessor=l->primeiro;
	l->primeiro=n;
	l->tam++;
	return l->primeiro;
}

/*Remove o nó de uma lista, porém não destroi os dados*/
no *remover_no(no *rm,lista *l){
	if(!rm) return NULL;
	no *n=rm->antecessor;
	if(!n){
		l->primeiro=rm->sucessor;
	}
	else{
		n->sucessor=rm->sucessor;
	}
	n=rm->sucessor;
	if(!n){
		l->ultimo=rm->antecessor;
	}
	else{
		n->antecessor=rm->antecessor;
	}
	l->tam--;
	return rm;
}

/*Para destruir um no*/
void destruir_no(no *n,lista *l)
{
	n=remover_no(n,l);
	free(n);
}
