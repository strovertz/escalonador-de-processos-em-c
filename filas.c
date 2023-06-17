#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "filas.h"
#include "untils.h"


Fila* fila_cria(void){
	Fila* f = (Fila*) malloc(sizeof(Fila));
	f->ini = f->fim = NULL;

	return f;
}

int fila_tam(Fila* f){
	int tam;
	Process *p = f->ini;
	if (p->prox == NULL)
	{
		return 0;
	}
	
	while (p->prox != NULL) 	{
		tam++;
	}
	return tam;
}

void fila_insere_ready(Fila* r, Process* n){
	Process* l = (Process*) malloc(sizeof(Process));
	l->queuetime = n->queuetime;
    l->id = n->id;
    l->IO = n->IO;
    l->tam = n->tam;
	l->prox = NULL;

	if(r->fim != NULL)
		r->fim->prox = l;
	else
		r->ini = l;

	r->fim = l;
}

void fila_insere_arrive(Fila* f){
	Process* l = (Process*) malloc(sizeof(Process));
	l->queuetime = clock();
    l->id = rand()%90;
    l->IO = rand()%2;
	l->tam = rand()%10;
	while (l->tam<=0) l->tam = rand()%10;
	l->pr = rand()%10;
	l->prox = NULL;
	
	if(f->fim != NULL)
		f->fim->prox = l;
	else
		f->ini = l;

	f->fim = l;
}

Process* fila_retira(Fila* f){
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

void fila_imprime(Fila* f){
	Process* l;
	for(l = f->ini; l != NULL; l = l->prox)
		printf("Process ID: %d;\n	Time Stamp: %d\n	CPU times Needed: %d\n", l->id, l->queuetime, l->tam);
}

int fila_vazia(Fila* f){
	return(f->ini == NULL);
}	

void fila_libera(Fila* f){
	Process* l = f->ini;
	Process* q = l;
	while(q != NULL){
		l = q->prox;
		free(q);
		q = l;
	}
	free(f);
}	