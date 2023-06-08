// fila representada como vetor (fila circular) e como lista.
// para compilar use: gcc -o main main.c filas_lista.c filas_vetor.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filas_vetor.h"
#include "filas_lista.h"


void fila_vet(void);
void fila_list(void);

int	main(){
	int op;

	do{
		printf("\t1 - Fila como vetor\n\t2 - Fila como lista\n\t3 - Sair\n\tEscolha: ");
		scanf("%d", &op);
		printf("\n");

		switch(op){
			case 1: fila_vet();
				break;
			case 2:	fila_list();
				break;
			case 3: printf("Saindo.");
				break;
			default: printf("Opcao invalida digite novamente.");
		}
		printf("\n"); 
	}while(op != 3);

	return 0;
}

void fila_vet(void){
	Fila_vetor* f = filaVetor_cria();
	int op, valor;

	do{
		printf("1 - Inserir\n2 - Remover\n3 - Imprimir\n4 - Sair\nEscolha:  ");
		scanf("%d", &op);
		printf("\n");
		switch(op){
			case 1: printf("Digite o valor: ");
					scanf("%d", &valor);
					filaVetor_insere(f, valor);
				break;
			case 2: if(filaVetor_vazia(f))
						printf("Remocao impossivel. A fila esta vazia.\n");
					else{
						valor = filaVetor_retira(f);
						printf("Valor removido: %d.", valor);
					}
				break;
			case 3:	 if(filaVetor_vazia(f)){
						printf("Impressao impossivel. A fila esta vazia.\n");
					 }
					 else{
					 	printf("\nFila: ");
						filaVetor_imprime(f);
					}
				break;
			case 4: printf("Fim.");
				break;
			default: printf("Opcao invalida. Digite novamente.");
		}
		printf("\n\n");
	}while(op != 4);

	filaVetor_libera(f);
}

void fila_list(void){
	Fila_lista* f = filaLista_cria();
	int op, valor;

	do{
		printf("1 - Inserir\n2 - Remover\n3 - Imprimir\n4 - Sair\nEscolha:  ");
		scanf("%d", &op);
		printf("\n");
		switch(op){
			case 1: printf("Digite o valor: ");
					scanf("%d", &valor);
					filaLista_insere(f, valor);
				break;
			case 2: if(filaLista_vazia(f))
						printf("Remocao impossivel. A fila esta vazia.\n");
					else{
						valor = filaLista_retira(f);
						printf("Valor removido: %d.", valor);
					}
				break;
			case 3:	 if(filaLista_vazia(f)){
						printf("Impressao impossivel. A fila esta vazia.\n");
					 }
					 else{
					 	printf("\nFila: ");
						filaLista_imprime(f);
					}
				break;
			case 4: printf("Fim.");
				break;
			default: printf("Opcao invalida. Digite novamente.");
		}
		printf("\n\n");
	}while(op != 4);

	filaLista_libera(f);
}

