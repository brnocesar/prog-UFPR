#include <stdio.h>

float potencia(float base, int expoente){
	float resultado;
	resultado = 1.0;
	while(expoente > 0){
		resultado *= base;
		expoente--;
	}
	return resultado;
}

int fatorial(int num){
	float resultado;
	resultado = 1.0;
	while(num > 0){
		resultado *= num;
		num--;
	}
	return resultado;
}

int main(){
	int i;
	float angulo, coseno;
	angulo = 2.0;
	
	for(i=0; i<14; i++){
		printf("\n( %f )", (float)potencia(-1, i) * (float)(potencia(angulo, 2*i) / (float)fatorial(2*i)));
		coseno += potencia(-1, i) * (potencia(angulo, 2*i) / fatorial(2*i));
	}
	printf("coseno de %f radianos = %f", angulo, coseno);
}