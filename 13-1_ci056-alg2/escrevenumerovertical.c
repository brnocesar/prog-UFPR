#include <stdio.h>

void escreve_1(int num) {

	if (num > 0) {

		escreve_1(num-1);
		printf(" %d\n", num);
	}
}

void escreve_2(int num) {

	if (num > 0) {

		printf(" %d\n", num);
		escreve_2(num-1);
	}
}

int main() {
    
	int numero;
	printf("digite um numero maior que zero: ");
	scanf("%d", &numero);
	
	escreve_1(numero);
	printf("\n");
	escreve_2(numero);
}