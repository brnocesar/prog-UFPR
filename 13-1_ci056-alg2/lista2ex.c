#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODO {
	int i;
	struct NODO *anterior;
	struct NODO *proximo;
} NODO;

typedef struct PILHA {
	int tamanho_pilha;
	NODO *primeiro;
	NODO *ultimo;
} PILHA;

typedef struct FILA {
	int tamanho_fila;
	NODO *primeiro;
	NODO *ultimo;
} FILA;

/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ exercicio (5) _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ */
FILA *cria_fila(void){}/*exercicio (5)*/
NODO *insere_numero_novo_nodo(int num, FILA *lista) {
    /* passo o numero que vai ser inserido na lista, 
    ando ate o ultimo elemento (que o objeto "proximo" aponta p/ NULL), 
    crio um novo item (apontado pelo objeto "proximo" do atual ultimo item da lista) e 
    coloco o numero nesse (novo ultimo) item da lista*/
}/*exercicio (5)*/
void outra_main() {
	int entrada;
	FILA *par, *impar;
	par = cria_fila();
	impar = cria_fila();
	
	do {
		printf("digite um numero: ");
		scanf("%d\n", &entrada);
		
		if ( !(entrada % 2) ) { /*se for numero par*/
			insere_numero_novo_nodo(entrada, par);
		}
		else insere_numero_novo_nodo(entrada, impar);
	} while (entrada);
	
	PILHA *final;
	entrada = 0;
	while ((aux_p != NULL) && (aux_i != NULL)) {
		if (++entrada % 2) { /*se for impar*/
			
		}
		
		aux_p = aux_p->proximo;
		aux_i = aux_i->proximo;
	}
}/*exercicio (5)*/

/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ exercicio (4) _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ */
NODO *remove_nodo(NODO *removido) {
    /*remove um noh (item) da lista e retorna o endereco do item seguinte*/
}/*exercicio (3)*/
int *mmm(FILA *f) {
	NODO *aux;
	aux = f->primeiro;
	int tam, *v; /*v[0]: maior, v[1]: menor, v[2]: media*/
	tam = f->tamanho_fila;
	v = (int*) malloc(3*sizeof(int));
	
	while(aux) {
		v[3] += aux->i; /*somatorio dos valores*/
		if ((aux->i) > v[0]) {
			v[0] = aux->i; /*pega o maior valor*/
			aux = remove_nodo(aux);
		}
		else if ((aux->i) < v[1]) {
			v[1] = aux->i; /*pega o menor valor*/
			aux = remove_nodo(aux);
		}
		
		aux = aux->proximo; /*atualiza o ponteiro*/
	}
	
	v[3] /= tam; /*faz a media pelo numero de elementos*/
	return v;
}/*exercicio (3)*/
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ exercicio (3) _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ */

void troca(NODO *um, NODO *dois){}/*exercicio (2)*/
PILHA *cria_pilha(void){}/*exercicio (2)*/
void troca_pilha(PILHA *inicial, PILHA *final, NODO *movido) { 
    /*o item ("movido") de uma lista (pilha) que inicialmente esta em "inicial" eh movido p/ outra lista (pilha) "final"*/
}/*exercicio (2)*/
PILHA *ordena_pilha(PILHA *header) {
	PILHA *ordenada;
	ordenada = cria_pilha();
	NODO *aux, *maior;
	
	while(header->tamanho_pilha--) { /*condicao do loop: tamanho da pilha que foi passada*/
		maior = header->primeiro;
		aux = (header->primeiro)->proximo;
		
		while(aux) {
			if ((aux->i) > (maior->i)) maior = aux; /*pega o maior*/
			aux = aux->proximo; /*atualiza ponteiro*/	
		}/*o ponteiro "maior" sempre vai estar apontando p/ o item com maior valor, quando sair deste loop*/
		
		troca_pilha(header, ordenada, maior); /*o item com maior valor eh trocado de lista*/
	}
	
	return ordenada;
}/*exercicio (2)*/

int main() {
	
}