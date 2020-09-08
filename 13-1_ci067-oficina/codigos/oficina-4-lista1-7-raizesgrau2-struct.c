//usar registrador
#include <stdio.h>
#include <math.h>
#define N 30

void imprime_matriz(int matriz[][N], int tamanho, int lim_coluna){
	int i, j;
	for(i=0; i<tamanho; i++){
		printf(" %d.\t|", i+1);
		for(j=0; j<lim_coluna; j++){
			printf(" %d |", matriz[i][j]);
		}
		printf("\n");
	}
}

void calcula_raizes(int a, int b, int c, int *x1, int *x2){
	int delta;
	delta = sqrt(b*b + 4*a*c);
	
	if(delta < 0) ;
	if(delta == 0){
		*x1 = (-b)/(2*a);
		*x2 = *x1;
	}
	
}

int main(){
	int coef[N][N], raiz[N][N], tam, i, j, duplo, triplo;
	triplo=3;
	duplo=2;
	
	printf("digite o numero de sequencias quer calcular (maximo %d): ", N);
	scanf("%d", &tam);
	if(tam > N) tam = N;
	
	for(i=0; i<tam; i++){
		printf("digite os coeficientes da equacao do segundo grau p/ #%d linha(inteiros): ", i+1);
		for(j=0; j<triplo; j++) scanf("%d", &coef[i][j]);
	}
	
	imprime_matriz(coef, tam, triplo); //imprime coeficientes
 	imprime_matriz(raiz, tam, duplo); //imprime raizes
	
	return 0;
}