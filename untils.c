#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
#include "untils.h"
// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Fila* r, Fila* a, int  tempo_maximo){
    Process* n = fila_retira(a);
    fila_insere_processo(r, n);
    trace_print(tempo_maximo,9, n->id, 0);
}

void* io_to_device(Lista* l, Fila* io, int  tempo_maximo){
    // fprintf("dando bo aq1\n\n");
    Process* p = ultimo(l);
    if(p != NULL){
        fila_insere_processo(io, p);
    } else trace_print(tempo_maximo,0,0,0);
}

void trace_print(int time, int selector, int process_id, int utils){
    FILE *text;
    text = fopen("traceFile.txt", "a"); // Abre o arquivo em modo de apêndice (append)

    if (text == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }

    switch (selector) {
        case 0:
            fprintf(text, "ERROR");
            break;
        case 1:
            fprintf(text, "[ETE %dms] Filas Criadas, exibindo estado atual:\n", (time+1000)*(-1));
            break;
        case 2:
            fprintf(text, "\n[ETE %dms] -- INICIANDO PROCESSAMENTO --", (time+1000)*(-1));
            break;
        case 3:
            fprintf(text, "\n[ETE %dms] Process ID: %d | Qtd Slices: %d\n", (time+1000)*(-1), process_id, utils);
            break;    
        case 4:
            fprintf(text, "[ETE %dms] Sem Processos na Fila, Aguardando chegada", (time+1000)*(-1));
            break;
        case 5:
            fprintf(text, "[ETE %dms] Restam %d Slices para encerrar o processo %d\n", (time+1000)*(-1), utils, process_id);
            break;
        case 6:
            fprintf(text, "[ETE %dms] Processo %d encerrado\n", (time+1000)*(-1), process_id);
            break;
        case 7:
            fprintf(text, "[ETE %dms] Processo %d em I/O\n", (time+1000)*(-1), process_id); 
            break;
        case 8:
            fprintf(text, "[ETE %dms] Processo %d solicitou IO - Valor de Prioridade: %d\n", (time+1000)*(-1), process_id, utils); 
            break;
        case 9:
            fprintf(text, "[ETE %dms]  Processo %d migrou para fila Ready\n", (time+1000)*(-1), process_id);
            break;
        case 10:
            fprintf(text,"[ETE %dms] Processo %d chegou na fila Arrive com Tamanho: %d\n", (time+1000)*(-1), process_id, utils);
            break;
        default:
            fprintf(text, "Error $404 Selector Not Found;");
            break;
    }

    fclose(text); // Fecha o arquivo após escrever nele
}
