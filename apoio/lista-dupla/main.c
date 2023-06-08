// gcc -o main main.c listas.c

#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

void main(){
	Lista* l = lst_cria();
	int valor;

	printf("Digite os valores (-1 fim): ");
	scanf("%d", &valor);

	while(valor != -1){
		l = lst_insere(l, valor);
		scanf("%d", &valor);
	}

	printf("Lista:\n");
	lst_imprime(l);
	printf("Digite o valor (vai ser removido o elemento anterior a ele): ");
	scanf("%d", &valor);

	l = lst_retira_ant(l, valor);

	printf("Lista:\n");
	lst_imprime(l);

	lst_desaloca(l);
}
