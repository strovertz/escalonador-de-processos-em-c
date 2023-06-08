#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "filas.h"

Arrive* arrive_cria(void){
	Arrive* f = (Arrive*) malloc(sizeof(Arrive));
	f->ini = f->fim = NULL;

	return f;
}

void arrive_insere(Arrive* f, int valor){
	Process* l = (Process*) malloc(sizeof(Process));
	l->queuetime = clock();
    l->id = rand()%90;
    l->IO = rand()%2;
	l->prox = NULL;

	if(f->fim != NULL)
		f->fim->prox = l;
	else
		f->ini = l;

	f->fim = l;
}

Process* arrive_retira(Arrive* f){
    if (f->ini == NULL) {
        // A fila está vazia, não há elementos para remover
        return NULL;
    }
    Process* l = f->ini;
    int id_removido = l->id;
    f->ini = l->prox;

    if (f->ini == NULL) {
        f->fim = NULL;
    }
    return l;
}

void arrive_imprime(Arrive* f){
	Process* l;
	for(l = f->ini; l != NULL; l = l->prox)
		printf("Process ID: %d;\nTime Stamp: %d\nCPU times Needed", l->queuetime, l->id);
}

int arrive_vazia(Arrive* f){
	return(f->ini == NULL);
}	

void arrive_libera(Arrive* f){
	Process* l = f->ini;
	Process* q = l;
	while(q != NULL){
		l = q->prox;
		free(q);
		q = l;
	}
	free(f);
}	