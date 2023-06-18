#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Fila* r, Fila* a){
    Process* n = fila_retira(a);
    fila_insere_processo(r, n);
    printf("[ETE %.1fms]  Processo %d migrou para fila Ready\n", (double)(clock() - begin), n->id);
}

void* io_to_device(Lista* l, Fila* io){
    Process* p = ultimo(l);
    // Marca que esta fazendo io
    printf("dando bo aq1\n\n");
    fila_insere_processo(io, p);
    printf("dando bo aq2\n\n");
}

void trace_print(int selector, process_id, utils){
    switch (selector) {
        case <=0:
            printf("ERROR");
            exit(1);
            break;
        case 1:
            printf("[ETE %.1fms] Filas Criadas, exibindo estado atual:\n", (double)(clock() - begin));
            break;
        case 2:
            printf("\n[ETE %.1fms] -- INICIANDO PROCESSAMENTO --",(double)(clock() - begin));
            break;
        case 3:
            printf("\n[ETE %.1fms] Process ID: %d\nQtd Slices: %d\n", (double)(clock() - begin), process_id, utils);
            break;    
        case 4:
            printf("[ETE %.1fms]Sem Processos na Fila, Aguardando chegada", (double)(clock() - begin));
            break;
        case 5:
            printf("[ETE %.1fms] Restam %d Slices para encerrar o processo %d PR %d\n", (double)(clock() - begin), utils, process_id);
            break;
        case 6:
            printf("[ETE %.1fms] Processo %d encerrado\n", (double)(clock() - begin), process_id);
            break;
        case 7:
            printf("[ETE %.1fms] Processo %d em I/O\n",  (double)(clock() - begin), p->id); 
        case :
            printf("[ETE %.1fms] Processo %d solicitou IO - Valor de Prioridade: %d\n",  (double)(clock() - begin), process_id, utils); 
            break;
        default:
            printf("Error $404 Selector Not Found;");
            break;
    }
}