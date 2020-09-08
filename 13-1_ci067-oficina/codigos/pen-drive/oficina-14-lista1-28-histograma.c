#include <stdio.h>
#define N 5

void histograma(int sequencia[], int histo[]){
	int i, j, casa, marcador, vezes;
	casa = 0;
	
	for(i=0; i<N; i++) histo[i] = 0; //inicializa histograma

	for(i=0; i<N; i++){
		marcador = -1;
		for(j=0; j<N; j++){
			if(sequencia[i] == histo[j]){
				marcador++;
				break;
			}
		} //verifica o todo o vetor di histograma
		/*se nao encontrou nenhum igual no vetor histograma, coloca o valor na primeiro elemento vazio*/
		if(marcador){
			histo[casa] = sequencia[i];
			casa++;
		}
	}

	printf("N = %d\n", N);
	for(i=0; i<N; i++){
		printf("%d ", sequencia[i]);
	}
	printf("\na sequencia tem os numeros distintos: ");
	for(i=0; i<casa; i++){
		printf(" %d ", histo[i]);
	}
	printf("\n");
	for(i=0; i<casa; i++){
		vezes = 0;
		printf("%d ", histo[i]);
		for(j=0; j<N; j++){
			if(histo[i] == sequencia[j]) vezes++;
		}
		printf(" %d\n", vezes);
	}

}

void recebe_vetor(int vetor[]){
	int i;
	
	printf("digite %d elementos: ", N);
	for(i=0; i<N; i++) scanf("%d", &vetor[i]);
}

int main(){
	int vet[N], copia[N];

	recebe_vetor(vet);
	
	histograma(vet, copia);

	return 0;
}
