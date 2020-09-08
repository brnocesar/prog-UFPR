//incompleto: subtraindo valor 5 das raizes
#include <stdio.h>
#include <math.h>
#define N 30

int calcula_raizes(int a, int b, int c, float *x1, float *x2){
	float delta;
	delta = (b*b) - (4*a*c);
	
	if(delta < 0) return 0; //nao tem raizes reais
	if(delta == 0){
		*x1 = (float)(-b)/(2*a);
		*x2 = 0;
		return 1;
	} //tem apenas UMA raiz real
	else{
		*x1 = (float)((-b) + sqrt(delta))/(2*a);
		*x2 = (float)((-b) - sqrt(delta))/(2*a);
		return 2;
	} //delta > 0, tem DUAS raizes reais
}

int main(){
	char condicao;
	condicao = 'a';
	int coef[N][3], tam, i, j, controle;
	float raiz[N][2];
	
	for(;;){
		printf("digite o numero de sequencias quer calcular (maximo %d): ", N);
		scanf("%d", &tam);
		if(tam > N) tam = N;
		
		for(i=0; i<tam; i++){
			printf("digite os coeficientes da equacao do segundo grau p/ #%d linha(inteiros): ", i+1);
			for(j=0; j<3; j++) scanf("%d", &coef[i][j]);
		} //recebe os coeficientes do polinomio
		
		for(i=0; i<tam; i++){
			printf("|");
			for(j=0; j<3; j++){
				printf(" %d |", coef[i][j]);
			} //imprime coeficientes
			
			controle = calcula_raizes(coef[i][0], coef[i][1], coef[i][2], &raiz[i][0], &raiz[i][1]);
			
			if(controle == 0){
				printf("\tnao existem raizes reais.\n");
				continue;
			}
			if(controle == 1){
				printf("\texiste UMA raiz real.\t");
				printf("| %g |\n", raiz[i][0]);
				continue;
			}
			if(controle == 2){
				printf("\texistem duas raizes reais.\t");
				printf("| %g | %g |\n", raiz[i][0], raiz[i][1]);
			}
		}
		printf("digite T p/ encerrar\nqualquer letra p/ continuar\n");
		scanf("%s", &condicao);
		if(condicao == 'T') return 0;
	}
}