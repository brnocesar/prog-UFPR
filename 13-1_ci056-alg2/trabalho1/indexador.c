#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista{
	char *palavra;
	int npalavra;
	int *linha;
};

lista* lista_plv;
int tam_lista_plv,cont_linha;

void leitura(arquivo);

void escrita();

void busca(char palavra[]);

void troca(int a,int b);

void inserir_palavra(char palavra_lida[],int local)
{
	int fim;
	if(strcmp(palavra_lida,lista_plv[m].palavra)!=0)
	{
		lista_plv[local].npalavra++;
		lista_plv[local].linha=(int*)realloc(lista_plv[local].linha,npalavra*sizeof(int));
		lista_plv[local].linha[npalavra-1]=cont_linha;
	}
	else
	{
		tam_lista_palavra++;
		lista_plv=(lista*)realloc(lista_plv,tam_lista_plv*sizeof(lista));
		strcpy(lista_plv[tam_lista_plv].palavra,palavra_lida);
		lista_plv[tam_lista_plv-1].npalavra=1;
		lista_plv[tam_lista_plv-1].linha=(int*)malloc(sizeof(int));
		lista_plv[tam_lista_plv-1].linha[0]=cont_linha;
		fim=tam_lista_plv;
		ordena(local,fim);
	}
}

void ordena(int local,int fim)
{
	if(fim<=local){return 0;}
	troca(fim,fim-1);
	return ordena(local,fim-1);
}
	
int main()
{

}
