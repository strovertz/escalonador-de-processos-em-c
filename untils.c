#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
#include "untils.h"
// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Fila* r, Fila* a){
    Process* n = fila_retira(a);
    fila_insere_processo(r, n);
    trace_print(9, n->id, 0);
}

void* io_to_device(Lista* l, Fila* io){
    // fprintf("dando bo aq1\n\n");
    Process* p = ultimo(l);
    if(p != NULL){
        fila_insere_processo(io, p);
    } else trace_print(0,0,0);
}

void trace_print(int selector, int process_id, int utils){
    FILE *text;
    text = fopen("output.txt", "a"); // Abre o arquivo em modo de apêndice (append)

    if (text == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }

    switch (selector) {
        case 0:
            fprintf(text, "ERROR");
            break;
        case 1:
            fprintf(text, "[ETE %.1fms] Filas Criadas, exibindo estado atual:\n", (double)(clock()));
            break;
        case 2:
            fprintf(text, "\n[ETE %.1fms] -- INICIANDO PROCESSAMENTO --", (double)(clock()));
            break;
        case 3:
            fprintf(text, "\n[ETE %.1fms] Process ID: %d | Qtd Slices: %d\n", (double)(clock()), process_id, utils);
            break;    
        case 4:
            fprintf(text, "[ETE %.1fms] Sem Processos na Fila, Aguardando chegada", (double)(clock()));
            break;
        case 5:
            fprintf(text, "[ETE %.1fms] Restam %d Slices para encerrar o processo %d\n", (double)(clock()), utils, process_id);
            break;
        case 6:
            fprintf(text, "[ETE %.1fms] Processo %d encerrado\n", (double)(clock()), process_id);
            break;
        case 7:
            fprintf(text, "[ETE %.1fms] Processo %d em I/O\n", (double)(clock()), process_id); 
            break;
        case 8:
            fprintf(text, "[ETE %.1fms] Processo %d solicitou IO - Valor de Prioridade: %d\n", (double)(clock()), process_id, utils); 
            break;
        case 9:
            fprintf(text, "[ETE %.1fms]  Processo %d migrou para fila Ready\n", (double)(clock()), process_id);
            break;
        case 10:
            fprintf(text,"[ETE %.1fms] Processo %d chegou na fila Arrive com Tamanho: %d\n", (double)(clock()), process_id, utils);
            break;
        default:
            fprintf(text, "Error $404 Selector Not Found;");
            break;
    }

    fclose(text); // Fecha o arquivo após escrever nele
}
