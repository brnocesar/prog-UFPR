#include <stdio.h>
#define n 3

struct perfil{
	char nome[50];
	char profissao[20];
	int data_nascimento[3];
	int salario;		
};


void imprime(struct perfil modelo[]){
    int i, j, data_hoje[3];
	
	printf("data de hoje: ");
	for(j=0; j<3; j++) scanf("%d", &data_hoje[j]);
	
	for(i=0; i< n; i++){
		printf("\nnome: %s", modelo[i].nome);
		printf("profissao: %s", modelo[i].profissao);
		printf(" %d anos\n", data_hoje[2] - modelo[i].data_nascimento[2]);
		printf("salario: %d", modelo[i].salario);
	}
	printf("\n\n");
}

int main(){
	int i, j;
	struct perfil homem[n];
	
	i = 0;
	while(i < n){
		printf("nome: ");
		fgets(homem[i].nome, 40, stdin);
		printf("profissao: ");
		fgets(homem[i].profissao, 18, stdin);		
		printf("data de nascimento (dd/mm/aaaa): ");
		for(j=0; j<3; j++) scanf("%d", &homem[i].data_nascimento[j]);
		printf("salario: ");
		scanf("%d", &homem[i].salario);
		i++;
	}
	
	
	imprime(homem);
	
	return 0;
}