#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int main(){
	/*declaracao do registro, struct*/
	struct contato{
	char nome[50];
	char enderesso[150];
	char telefone[16];
	char email[50];
	char cidade[20];
	char cep[12];
	char estado[10];
	};

	struct contato agenda[N]; /*array de nome agenda do tipo contato*/

	int i;
	i=0;
	while(i < N){
		printf("\ndigite as informacoes do #%d contato.\n", i+1);
		printf("nome:");
		fgets(agenda[i].nome, 50, stdin); /*fgets(vetor, numero_maximo_caracteres, referencia ao input (pelo teclado)*/
		if(agenda[i].nome[0] == '\n') break;
		printf("endereço (nome da rua, numero, bairro):");
		fgets(agenda[i].enderesso, 150, stdin);
		printf("telefone (ddd)xxxx-yyyy:");
		fgets(agenda[i].telefone, 16, stdin);
		printf("e-mail:");
		fgets(agenda[i].email, 50, stdin);
		printf("cidade:");
		fgets(agenda[i].cidade, 20, stdin);
		printf("cep:");
		fgets(agenda[i].cep, 12, stdin);
		printf("estado:");
		fgets(agenda[i].estado, 10, stdin);
		i++;
	}

	char busca_nome[50];
	printf("\ndigite o nome de um dos contatos: ");
	fgets(busca_nome , 50, stdin);

	for(i=0; i<N; i++){
		if(!strcmp(agenda[i].nome, busca_nome)){
			printf("endereço: %se-mail: %s\n", agenda[i].enderesso, agenda[i].email);
		}
	}
}
