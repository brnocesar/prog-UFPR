/*Trabalho de Algoritmos e Estrutura de Dados II
1º Semestre de 2013*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Definição de tipos (tipo lista para guardar as palavras lidas)*/
typedef struct{
	char *palavra;/*Palavra Lida*/
	int npalavra;/*Numero de vezes que a palavra é encontrada no documento*/
	int *linha;/*Linhas onde ela foi encontrada*/
}lista;

/*Declaração de variaveis globais*/
lista* lista_plv,lista_aux;/*lista_aux para auxiliar na troca*/
int tam_lista_plv,conta_linha;

/*Declaração de Funções*/

void copia(int v1[],int v2[],int tam);

/*Lê uma palavra no documento, coloca em minuscala, ignora pontuação, conta linha*/
void leitura(char *arq);

/*Escreve o vetor de estrutura no arquivo de saida*/
void escrita();

/*Função embalagem para busca binaria bb*/
int busca(char palavra[]);

/*Busca binaria para strings*/
int bb(char palavra[],int inf,int sup);

/*Troca as posições entre dois elementos do vetor de estruturas (auxilia na função ordena)*/
void troca(int a,int b);

/*Inseri uma palavra lida no vetor de estrutura (incrementa contadores se ja existe)*/
void inserir_palavra(char palavra_lida[],int local);

/*Ordena o vetor de estrutura*/
void ordena(int local,int fim);


/*Menu Principal*/
int main(char argc,char *argv[])
{
	FILE *arquivo;
	char palavra_lida[60];
	int local;
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
  	tam_lista_plv=0;
  	conta_linha=1;
  	lista_plv=(lista*)malloc(sizeof(lista));
  	lista_plv[0].palavra=(char*)malloc(2*sizeof(char));
  	lista_plv[0].palavra="#\0";
  	leitura(argv[1]);
  	escrita();
}


/*Implementação das funções*/

void troca(int a, int b){
 	lista aux;
 	aux.palavra=(char*)malloc(strlen(lista_plv[a].palavra)*sizeof(char));
 	strcpy(aux.palavra,lista_plv[a].palavra);
 	aux.npalavra=lista_plv[a].npalavra;
 	aux.linha=(int*)malloc((aux.npalavra+1)*sizeof(int));
 	copia(aux.linha,lista_plv[a].linha,aux.npalavra+1);
 	
 	lista_plv[a].palavra=(char*)realloc(lista_plv[a].palavra,strlen(lista_plv[b].palavra)*sizeof(char));
 	strcpy(lista_plv[a].palavra,lista_plv[b].palavra);
 	lista_plv[a].npalavra=lista_plv[b].npalavra;
 	lista_plv[a].linha=(int*)realloc(lista_plv[a].linha,(lista_plv[b].npalavra+1)*sizeof(int));
 	copia(lista_plv[a].linha,lista_plv[b].linha,lista_plv[b].npalavra+1);
 	
 	lista_plv[b].palavra=(char*)realloc(lista_plv[b].palavra,strlen(aux.palavra)*sizeof(char));
 	strcpy(lista_plv[b].palavra,aux.palavra);
 	lista_plv[b].npalavra=aux.npalavra;
 	lista_plv[b].linha=(int*)realloc(lista_plv[b].linha,(aux.npalavra+1)*sizeof(int));
 	copia(lista_plv[b].linha,aux.linha,aux.npalavra+1);
} /*troca os elementos da estrutura dos indices que recebe*/

void inserir_palavra(char palavra_lida[],int local)
{
	/*Caso a palavra já exista em lista_plv, incrementa contadores*/
	if(strcmp(palavra_lida,lista_plv[local].palavra)==0)
	{
		lista_plv[local].npalavra++;
		printf("aqui1\n");
		lista_plv[local].linha=(int*)realloc(lista_plv[local].linha,(lista_plv[local].npalavra+1)*sizeof(int));
		printf("aqui2\n");
		lista_plv[local].linha[lista_plv[local].npalavra-1]=conta_linha;
		printf("aqui4\n");
		/*Serve para não fazer comparação com elementos que não existam no vetor*/
		lista_plv[local].linha[lista_plv[local].npalavra]=-1;
		printf("aqui5\n");
	}
	/*Caso não exista, aloca um espaço e inseri no final de lista_plv*/
	else
	{
		tam_lista_plv++;
		lista_plv=(lista*)realloc(lista_plv,(tam_lista_plv+1)*sizeof(lista));
		lista_plv[tam_lista_plv].palavra="#\0";
		lista_plv[tam_lista_plv-1].palavra=(char*)malloc((strlen(palavra_lida)+1)*sizeof(char));
		strcpy(lista_plv[tam_lista_plv-1].palavra,palavra_lida);
		lista_plv[tam_lista_plv-1].npalavra=1;
		/*Dois porque pode colocar um elemento pivo*/
		lista_plv[tam_lista_plv-1].linha=(int*)malloc(2*sizeof(int));
		lista_plv[tam_lista_plv-1].linha[0]=conta_linha;
		/*Serve para não fazer comparação com elementos que não existam no vetor*/
		lista_plv[tam_lista_plv-1].linha[1]=-1;
		/*Agora ordena lista_plv*/
		ordena(local,tam_lista_plv-1);
	}
}

void ordena(int local,int fim)
{
	if(fim<=local){return;}
	troca(fim,fim-1);
	ordena(local,fim-1);
}

int busca(char palavra[])
{
    int inf,sup;
    inf=0;
    sup=tam_lista_plv-1;
    return bb(palavra,inf,sup);
}

int bb(char palavra_lida[],int inf,int sup)
{
    if(inf>sup)
        return inf;
    int meio=(inf+sup)/2;
    if(strcmp(palavra_lida,lista_plv[meio].palavra)==0)
        return meio;
    if(strcmp(palavra_lida,lista_plv[meio].palavra)>0)
        return bb(palavra_lida,meio+1,sup);
    else
        return bb(palavra_lida,inf,meio-1);
}

void escrita()
{
    FILE *saida;
    int i,j,cont;
    saida=fopen("teste.out","w");
    printf("==%d %d %d %d\n",lista_plv[1].linha[0],lista_plv[1].linha[1],lista_plv[5].linha[2],lista_plv[5].linha[3]);
    for(i=0;i<tam_lista_plv;i++)
    {
        fprintf(saida,"%s, %d, {",lista_plv[i].palavra,lista_plv[i].npalavra);
        j=0;
        while(lista_plv[i].linha[j]==lista_plv[i].linha[j+1])
            {j++; printf("aqui\n");}
        j++;
        printf("%d %d\n",i,j);
        fprintf(saida,"(%d,%d)",lista_plv[i].linha[0],j);
        while(j<lista_plv[i].npalavra)
        {
            cont=1;
            if(lista_plv[i].linha[j]==lista_plv[i].linha[j+1])
                cont++;
            else
                fprintf(saida,",(%d,%d)",lista_plv[i].linha[j],cont);
            j++;
        }
        fprintf(saida,"}\n");
    }
    fclose(saida);
}


void copia(int v1[], int v2[], int tam){
	int i;
	for(i=0; i<tam; i++) v1[i] = v2[i];
}

void leitura(char *arquivo){
		
	FILE *fp;
	fp = fopen(arquivo, "r"); /*abre o arquivo APENAS p/ leitura*/
 	char aux, *palavra;
	palavra = (char *) malloc(2*sizeof(char)); /*aloca espaco p/ 2 elementos char (primeiro caracter e terminador nulo)*/
	int i,local;
	i = 0;
	while(!feof(fp)){

		aux = tolower(getc(fp)); /*getc() pega um caracter do arquivo e tolower() converte para minuscula*/
		if((aux >= 'a' && aux <= 'z')||(aux >= '1' && aux <= '9')){
			palavra = (char *) realloc(palavra, (i+2)*sizeof(char)); /*realoco espaco p/ mais um elemento*/
			*(palavra + (i+1)) = 0; /*coloca o '\0' na ultima posicao*/
			*(palavra + i) = aux; /*coloca o caracter no ultimo elemento valido*/
			i++;
			continue;
		}
		else if(i)
		{								
			printf("%s\n-----------\n", palavra); /*teste de impressao, palavra COMPLETA*/
			local=busca(palavra); /*chama funcao que procura a palavra na strutura*/
			inserir_palavra(palavra,local);	
			i = 0;
			
			palavra = (char *) realloc(palavra, 2*sizeof(char));
		}
		else if(aux=='\n')
			conta_linha++;
 /*realoca espaco para dois elementos, comeca outra palavra*/
		/*pegou um caracter nao valido (pontuacao)*/
		
 	} /*feof() retorna ZERO quando chega no fim do arquivo*/

	fclose(fp);
}
