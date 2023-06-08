#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filas_vetor.h"

Fila_vetor* filaVetor_cria(void){
	Fila_vetor* f = (Fila_vetor*) malloc(sizeof(Fila_vetor));
	f->vet = (int*) malloc(N * sizeof(int));
	f->n = 0;
	f->ini = 0;

	return f;
}

void filaVetor_insere(Fila_vetor* f, int valor){
	int fim;

	if(f->n == N)
		printf("Capacidade da fila estorou. Elemento nao foi inserido.\n");

	else{
		fim = (f->ini + f->n) % N;
		f->vet[fim] = valor;	
		f->n++;	
	}
}

int filaVetor_retira(Fila_vetor* f){
	float v;

	v = f->vet[f->ini];
	f->ini = (f->ini + 1) % N;
	f->n--;

	return v;
}

void filaVetor_imprime(Fila_vetor* f){
	int inicio, fim, i;

	inicio = (f->ini + 1) % N;
	fim = (f->ini + f->n) % N;

	if(fim >= inicio){
		for(i = 0; i < fim; i++)
			printf("%d ", f->vet[i]);
	}
	else{
		for(i = inicio-1; i < N; i++)
			printf("%d ", f->vet[i]);
		for(i = 0; i < fim; i++)
			printf("%d ", f->vet[i]);
	}
}

int filaVetor_vazia(Fila_vetor* f){
	return (f->n == 0);
}

void filaVetor_libera(Fila_vetor* f){
	free(f);
}