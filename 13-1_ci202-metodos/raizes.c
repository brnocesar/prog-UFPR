#include <stdio.h>
#include <math.h>

float f(float x){
	return pow(x, 3) - (9 * x) + 3;
}

float f_linha(float x){
	return 3*pow(x, 2) - 9;
}

float bissecao(float a, float b, float erro){
	float m;
	m = (a+b)/2;
	
	if(fabs(b-a) <= erro) return m;
	
	if((f(a)*f(m)) < 0) return bissecao(a, m, erro);
	else
		return bissecao(m, b, erro);
}

float falsa_posicao(float a, float b, float erro){
	float m;
	m = a - ((b-a)*f(a)/(f(b)-f(a)));
	
	if((fabs(b-a) <= erro) || (f(m) <= erro)) return m;
	
	if((f(a)*f(m)) < 0) return falsa_posicao(a, m, erro);
	else
		return falsa_posicao(m, b, erro);
}

float newton_raphson(float a, float erro){
	float m;
	m = a - (f(a)/f_linha(a));
	
	if((fabs(m-a)) <= erro) return m;
	else
		newton_raphson(m, erro);
} /*comeca sempre pelo menor extremo, independendo se eh o mais adequado*/

int main(){
	float a, b, erro;
	
	printf("digite os extremos do intervalo [a:b], e a precisao (0.00X): ");
	scanf("%f%f%f", &a, &b, &erro);
	
	printf("bissecao: %f\n", bissecao(a, b, erro));
	printf("falsa posicao: %f\n", falsa_posicao(a, b, erro));
	printf("newton-raphson: %f\n", newton_raphson(a, erro));
	
	return 0;
}