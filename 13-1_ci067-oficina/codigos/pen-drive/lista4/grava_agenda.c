#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CONTATOS 50


int main(){
	struct contato{
		char nome[51];
		char endereco_postal[251];
		char fone[17];
		char email[51];
		char cidade[51];
		char cep[12];
		char estado[5];
	};

	struct contato agenda[CONTATOS];

	int i;
	i=0;
	while(i < CONTATOS){
		printf("\ndigite as informacoes do #%d contato.\n", i+1);
		printf("nome:");
		fgets(agenda[i].nome, 50, stdin); /*fgets(vetor, numero_maximo_caracteres, referencia ao input (pelo teclado)*/
		if(agenda[i].nome[0] == '\n') break;
		printf("endereço (nome da rua, numero, bairro):");
		fgets(agenda[i].endereco_postal, 250, stdin);
		printf("telefone (ddd)xxxx-yyyy:");
		fgets(agenda[i].fone, 16, stdin);
		printf("e-mail:");
		fgets(agenda[i].email, 50, stdin);
		printf("cidade:");
		fgets(agenda[i].cidade, 50, stdin);
		printf("cep:");
		fgets(agenda[i].cep, 11, stdin);
		printf("estado:");
		fgets(agenda[i].estado, 4, stdin);
		i++;
	}


	char arquivo[] = "agenda.dat";
	FILE *fp;

	fp = fopen(arquivo, "w");

	while(i > 0){
		fprintf(fp, "nome: %s", agenda[i].nome);
		fprintf(fp, "endereco: %s", agenda[i].endereco_postal);
		fprintf(fp, "cep: %s", agenda[i].cep);
		fprintf(fp, "cidade: %s", agenda[i].cidade);
		fprintf(fp, "estado: %s", agenda[i].estado);
		fprintf(fp, "fone: %s", agenda[i].fone);
		fprintf(fp, "email: %s", agenda[i].email);
		i--;
	}


	fclose(fp);
}
