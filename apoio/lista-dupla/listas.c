#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

Lista* lst_cria(void){
	return NULL;
}

// inserção no início: retorna a lista atualizada 
Lista* lst_insere(Lista* l, int v){
	Lista* novo = (Lista*) malloc(sizeof(Lista));

	novo->info = v;
	novo->prox = l;
	novo->ant = NULL;

	if(l != NULL)
		l->ant = novo;

	return novo;
}

/* 
// inserção no fim: retorna a lista atualizada 
Lista* lst_insere (Lista* l, int i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox=NULL;
	Lista* ult = ultimo(l);
	if (ult==NULL) //lista vazia
		l = novo;
	else //ha elementos na lista
		ult->prox=novo;
	novo->ant=ult;
	return l;
}
*/

// retorna ultimo elemento da lista
Lista* ultimo (Lista* l) {
	Lista* p = l;
	if (p != NULL) {
		while (p->prox != NULL)
			p= p->prox;
	}
	return p;
}

// função retira: função que remove o elemento anterior a um elemento de valor v
Lista* lst_retira_ant (Lista* l, int v){
	Lista* p = lst_busca(l, v);

	if(p == NULL || p == l){
		printf("Remocao impossivel\n");
		return l;
	}

	p = p->ant;

	if(p->ant == NULL) //primeiro elemento deve ser removido
		l = p->prox;
	else{
		p->ant->prox = p->prox;
		p->prox->ant = p->ant;
	}

	free(p);

	return l;
}

// função busca: busca um elemento na lista 
Lista* lst_busca(Lista* l, int v){
	Lista* p = l;

	while(p != NULL && p->info != v)
		p = p->prox;
	

	return p;
}

void lst_imprime(Lista* l){
	Lista* p;
	for(p = l; p != NULL; p = p->prox)
		printf("%d ", p->info);

	printf("\n");
}

void lst_desaloca(Lista* l){
	Lista* p = l;

	while(p != NULL){
		l = p->prox;
		free(p);
		p = l;
	}
}


/*
Lista* insere_crescente(Lista* l, int valor){
	Lista* p = l;
	Lista* ant = NULL;
	
	while(p != NULL && p->info < valor){
		ant = p;
		p = p->prox;
	}
	
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = valor;
	
	if(ant == NULL){ //insere no inicio
		novo->prox = l;
		l = novo;
	}
	else{ //insere meio ou fim
		novo->prox = ant->prox;
		ant->prox = novo;
	}
		
	return l;
}
*/
