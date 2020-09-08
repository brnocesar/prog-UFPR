/* Exemplo usando arguentos de linha de comando,
 * arquivos, ponteiros e arrays de ponteiros
 * Obtem frases do usuario e as grava em um arquivo. */

#include <stdio.h>
#include <string.h>

char *frases = {
  "Os  exercícios  abaixo são  exercícios  preparatórios  para facilitar  a\
migração para a Linguagem C.\
Muitos dos exercícios abaixo já foram vistos em disciplinas introdutórias de\
Programação de  Computadores. Muitos deles foram  retirados ou adaptados\
de materiais dos  professores do DINF/UFPR \\htmladdnormallinkfoot{Marcos\
  Castilho}{http://www.inf.ufpr.br/cursos/ci055/},\
\\htmladdnormallinkfoot{Ionildo\
  Sanches}{http://br.geocities.com/ijsanches/programacao/download.htm} e\
\\htmladdnormallinkfoot{Carmem\
  Hara}{http://www.inf.ufpr.br/carmem/ci208/}.\
\
\\vtab\
\
\\section{Básicos}\
\
\\exercise{Afrânio tem um peso de 80 kg e está engordando uma média de 2\
  kg por ano.  Enquanto isto, Ermengarda, sua amada esposa, tem 45 kg e\
  está engordando  uma média  de 3  kg por ano.   Faça um  programa que\
  calcule e imprima quantos  anos serão necessários para que Ermengarda\
  ultrapasse o  peso de Afrânio.  O programa deve também  imprimir qual\
  será o peso de cada membro do casal ternura neste momento.}"
};


void gravaPutc(FILE *fp){
  	int i;

  	for (i=0; frases[i]; i++) fputc(frases[i], fp);
}


void gravaPuts(FILE *fp){
  	fputs(frases, fp);
}


void gravaPrintf(FILE *fp){
  	fprintf(fp, "%s", frases);
}


void gravaWrite(FILE *fp, int tam){
  	fwrite(frases, sizeof(char), tam, fp);
}


main (int argc, char *argv[]){

  	FILE *fp; /*ponteiro para arquivo*/
  	int tam, nfrs;

  	if (argc != 2) fprintf(stderr,"Forma de Uso: %s arquivo\n",argv[0]);
  	else{
    		fp = fopen (argv[1], "w+");
    		if (fp == NULL) fprintf(stderr, "Erro ao abrir arquivo %s\n", argv[1]);
    		else{
      		printf("Gravando texto com fputc() ... ");
      		gravaPutc(fp);
      		printf("feito\n");
      
      		rewind(fp);
      		printf("Gravando texto com fputs() ... ");
      		gravaPuts(fp);
      		printf("feito\n");
      
      		rewind(fp);
      		printf("Gravando texto com fprintf() ... ");
      		gravaPrintf(fp);
      		printf("feito\n");
      
      		rewind(fp);
      		printf("Gravando texto com fwrite() ... ");
      		tam = strlen(frases);
      		gravaWrite(fp, tam);
		      printf("feito\n");
    		}  /* FIM (fp == NULL) */
  	}
}

