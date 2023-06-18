#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "filas.h"
#include "untils.h"
clock_t begin;

Process* io(Lista* l, Fila* io){
    if(l->p == NULL) trace_print(0, 0, 0);
    if(io->ini == NULL && io->fim == NULL) {
        io_to_device(l, io);
    } 
    if(rand()%100>75) {
        io->ini->in_io = true;
    } 
    return io->ini;
}

Process* cpu(Process* p, int time_slice, Lista* l, Fila* io_device){
    if(p->tam < time_slice) {
        usleep(p->tam);
        p->tam = 0;
        return p;
    } else usleep(time_slice);
    if(p->IO == 1)  {
        if(rand()%100 > 75) {
            trace_print(8, p->id, p->pr);
            insere_crescente(l, p); 
            if(rand()%100 > 75) {
                io(l, io_device);
                return p; // retorna sem decrementar a time slice
            };
            p->tam = p->tam - time_slice; 
            return p;
        }
    }
    p->tam = p->tam - time_slice;
    return p;
}

void processa_ready(Fila* r, Fila * a,  int time_slice, int tempo_maximo, Lista* l){
    Fila* io_queue = fila_cria();
    Process* p = fila_retira(r);
    fila_imprime(r);
    trace_print(3,p->id, p->tam);
    if(p == NULL) {
        fila_insere_arrive(a); 
        trace_print(4,0,0);
        arrive_to_ready(r, a);
    }
    while (tempo_maximo != 0){      
        p = cpu(p, time_slice, l, io_queue);
        if(p->tam > 0 && !p->in_io) {
            fila_insere_processo(r, p); 
            trace_print(5,p->id,p->tam);
        } else if (!p->in_io) { 
            trace_print(6,p->id,0);
        } else trace_print(7,p->id,0);
        if(rand()%300>256) fila_insere_arrive(a);
        if(p->prox == NULL){
            for(int i = 0; i < rand()%10; i++) {
                fila_insere_arrive(a); 
                arrive_to_ready(r, a);
            }
        }
        p = fila_retira(r);
        tempo_maximo--;
    }
    if (tempo_maximo == 0)
    {
        printf("\n Tempo Max de Execucao Alcancado \n");
    }
}

void queue_init(Fila* r, Fila* a, int time_slice, int tempo_maximo){
    for (int i = 0; i < rand() %10; i++) {
        fila_insere_arrive(a);
        }
    fila_imprime(a);
    arrive_to_ready(r, a);
    fila_imprime(r);
    printf("\n");    
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: ./filename <NUM_MAX_DE_PROCESSOS\n");
        return 1;
    }
    Fila* arrive_queue = fila_cria();
    Fila* ready_queue = fila_cria();
    Lista* io_queue = lst_cria();
    int tempo_maximo = 100; 
    int time_slice = 2;
    trace_print(1, 0, 0);
    queue_init(ready_queue, arrive_queue, time_slice, tempo_maximo);
    trace_print(2,0,0);
    processa_ready(ready_queue, arrive_queue, time_slice, tempo_maximo, io_queue);
    return 0;
}