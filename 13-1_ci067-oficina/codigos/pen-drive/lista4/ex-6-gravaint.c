#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5


int main(){
	int vetor[N], i;
	for(i=0; i<N; i++){
		printf("digite o %d. numero: ", i+1);
		scanf("%d", &vetor[i]);
	} /*recebo os numeros*/
	
	char endereco[] = "arquivo_6.dat";
	FILE *fp; /*declaro um ponteiro para arquivo*/

	fp = fopen(endereco, "w+b"); /*abre o arquivo e retorna um ponteiro para o arquivo*/


	if(!fp) printf("erro ao abrir o arquivo!\n");
	else printf("\tarquivo aberto com sucesso!\n");


	fwrite(vetor, sizeof(int), N, fp);


	fclose(fp); /*fecha o arquivo*/
	
}
