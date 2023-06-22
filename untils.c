#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
#include "untils.h"
// função que tira da fila Arrive q joga pra fila Ready
int arrive_to_ready(Fila* r, Fila* a, int  tempo_atual){
    Process* n = fila_retira(a);
    fila_insere_processo(r, n);
    trace_print(tempo_atual,9, n->id, 0);
    tempo_atual++;
    return tempo_atual;
}

Fila* io_to_device(Process* p, Fila* io, int tempo_atual) {
    if (p != NULL) {
        fila_insere_processo(io, p);
        tempo_atual++;
    } else {
        trace_print(tempo_atual, 0, 0, 0);
    }

    return io;  // Retorna a fila de IO atualizada
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
            fprintf(text, "[ETE %dms] Filas Criadas, exibindo estado atual:\n", time);
            break;
        case 2:
            fprintf(text, "\n[ETE %dms] -- INICIANDO PROCESSAMENTO --", time);
            break;
        case 3:
            fprintf(text, "\n[ETE %dms] Process ID: %d | Qtd Slices: %d\n", time, process_id, utils);
            break;    
        case 4:
            fprintf(text, "[ETE %dms] Sem Processos na Fila, Aguardando chegada", time);
            break;
        case 5:
            fprintf(text, "[ETE %dms] Restam %d Slices para encerrar o processo %d\n", time, utils, process_id);
            break;
        case 6:
            fprintf(text, "[ETE %dms] Processo %d encerrado\n", time, process_id);
            break;
        case 7:
            fprintf(text, "[ETE %dms] Processo %d para fila de I/O\n", time, process_id); 
            break;
        case 8:
            fprintf(text, "[ETE %dms] Processo %d solicitou IO - Valor de Prioridade: %d\n", time, process_id, utils); 
            break;
        case 9:
            fprintf(text, "[ETE %dms]  Processo %d migrou para fila Ready\n", time, process_id);
            break;
        case 10:
            fprintf(text,"[ETE %dms] Processo %d chegou na fila Arrive com Tamanho: %d\n", time, process_id, utils);
            break;
        default:
            fprintf(text, "Error $404 Selector Not Found;");
            break;
    }

    fclose(text); // Fecha o arquivo após escrever nele
}
