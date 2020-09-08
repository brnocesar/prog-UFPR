#ifndef _lista_
#define _lista_

typedef void *objeto;

/* typedef ... no;    */

/* typedef ... lista; */

#if defined(_sequencial_)
typedef objeto no;

typedef struct { 
  no *v; 
  unsigned int capacidade, tamanho; 
#ifdef _dupla_entrada_  
  unsigned int primeiro; 
#endif
} lista;
#elif defined(_ligada_)
typedef struct no {
  objeto o;
  struct no *sucessor;
} no;

typedef struct {
  no *primeiro;
  unsigned int tamanho;
#ifdef _dupla_entrada_  
  no *ultimo; 
#endif
} lista;
#else
typedef void no;
typedef void lista;
#endif

objeto objeto_no(no *p);
no *sucessor_no(no *p, lista *l);
no *primeiro_no(lista *l);

int vazia_lista(lista *l);
unsigned int tamanho_lista(lista *l);
lista *constroi_lista(void);
void destroi_lista(lista *l);
no *insere_lista(objeto o, lista *l);
objeto remove_lista(lista *l);

#ifdef _dupla_entrada_  
no *insere_outra_ponta_lista(objeto o, lista *l);
#endif

#endif
