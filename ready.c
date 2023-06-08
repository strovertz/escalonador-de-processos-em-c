#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "filas.h"

Ready* ready_cria(void){
	Ready* f = (Ready*) malloc(sizeof(Ready));
	f->ini = f->fim = NULL;

	return f;
}

void ready_insere(Ready* f, Process* n){
	Process* l = (Process*) malloc(sizeof(Process));
	l->queuetime = n->queuetime;
    l->id = n->id;
    l->IO = n->IO;
	l->prox = NULL;

	if(f->fim != NULL)
		f->fim->prox = l;
	else
		f->ini = l;

	f->fim = l;
}

Process* ready_retira(Arrive* f){
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
void ready_imprime(Ready* f){
	Process* l;
	for(l = f->ini; l != NULL; l = l->prox)
		printf("Process ID: %d;\nTime Stamp: %d\n", l->queuetime, l->id);
}

int ready_vazia(Ready* f){
	return(f->ini == NULL);
}	

void ready_libera(Ready* f){
	Process* l = f->ini;
	Process* q = l;
	while(q != NULL){
		l = q->prox;
		free(q);
		q = l;
	}
	free(f);
}	