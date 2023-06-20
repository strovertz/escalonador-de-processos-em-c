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
	int tam = 0; 
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

void fila_insere_processo(Fila* r, Process* n){
	Process* l = (Process*) malloc(sizeof(Process));
	l->queuetime = n->queuetime;
    l->id = n->id;
    l->IO = n->IO;
    l->tam = n->tam;
	l->pr = n->pr;
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
	l->tam = (rand()%30)+1;
	l->in_io = false;
	l->pr = (rand()%5)+1;
	trace_print(10,l->id,l->tam);
	//printf("[ETE %.1fms] Processo %d chegou na fila Arrive com Tamanho: %d e Priodidade: %d\n", (double)(clock()), l->id, l->tam, l->pr);
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

Lista* lst_cria(void){

	return NULL;
}

// // inserção no início: retorna a lista atualizada 
// Lista* lst_insere(Lista* l, Process* p){
// 	Lista* novo, *aux = (Lista*) malloc(sizeof(Lista));
// 	novo->pr = p->pr;
// 	novo->prox = l;
// 	novo->ant = NULL;
// 	aux = novo;
// 	while (aux->prox != NULL)
// 	{
// 		aux->ini = novo;
// 		aux = aux->prox;
// 	}
// 	aux = aux->ini;
// 	novo = aux;
// 	if(l != NULL)
// 		l->ant = novo;

// 	return novo;
// }

/* 
// inserção no fim: retorna a lista atualizada 
Lista* lst_insere (Lista* l, int i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->pr = i;
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
Process* ultimo (Lista* l) {
	Lista* p = l;
	if (p != NULL) {
		while (p->prox != NULL)
			p= p->prox;
	}
	if(p->p == NULL ) printf("deu pau"); exit(0);
	return p->p;
}

// função retira: função que remove o elemento anterior a um elemento de pr v
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

	while(p != NULL && p->pr != v)
		p = p->prox;
	

	return p;
}

void lst_imprime(Lista* l){
	Lista* p;
	for(p = l; p != NULL; p = p->prox)
		printf("%d ", p->pr);

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

// void inserir_ordenado(Lista *p_io, int num){
//     Lista *aux, *novo = malloc(sizeof(Lista));

//     if(novo){
//         novo->pr = num;
//         if(p_io>inicio == NULL){
//             novo->prox = NULL;
//             p_io->inicio = novo;
//         }
//         else if(novo->pr < p_io->inicio->pr){
//             novo->prox = p_io->inicio;
//             p_io->inicio = novo;
//         }
//         else{
//             aux = p_io->inicio;
//             while(aux->prox && novo->pr > aux->prox->pr)
//                 aux = aux->prox;
//             novo->prox = aux->prox;
//             aux->prox = novo;
//         }
//         p_io->tam++;
//     }
//     else
//         printf("Erro ao alocar memoria!\n");
// }


Lista* insere_crescente(Lista* l, Process* proc) {
    Lista* p = (Lista*)malloc(sizeof(Lista));
	p = l;
    Lista* ant = NULL;
    Process* prc = (Process*)malloc(sizeof(Process));
	prc = proc;
    while (p != NULL && p->pr < prc->pr) {
        ant = p;
        p = p->prox;
    }

    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->p = prc;
    novo->pr = prc->pr;
    novo->ant = NULL; // Initialize ant pointer to NULL
    novo->prox = NULL; // Initialize prox pointer to NULL

	
    if (ant == NULL) { // insere no início
        novo->prox = l;
        if (l != NULL) {
            l->ant = novo;
        }
        l = novo;
    } else { // insere meio ou fim
        novo->prox = ant->prox;
        if (novo->prox != NULL) {
            novo->prox->ant = novo;
			
        }
        ant->prox = novo;
        novo->ant = ant;
    }
	 
    return l;
}

