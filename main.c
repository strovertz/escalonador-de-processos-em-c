#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "filas.h"
#include "untils.h"

// Processo é gerado e chega na arrive queue
// Tem espaço no Systema?  Tenta usar a CPU; Não tem ? espera na arrive até liberar.
// se a cpu estiver sendo utilizada Puxa pra Ready queue (FIFO)
// Senão, caso esteja livre, processa o time slice, 
// Não tem ? espera na arrive até liberar.

// Conseguiu a CPU? Executa até atender uma dessas condições:
// IF - Processo concluido, executa durante todo o tempo necessário pra conclusão dele
// Entra pra CPU o primeiro processo da fila de chegada, se n tiver processo na arrive, precisa puxar um gerador
// IF - Terminou a time slice, interrompe a execução do processo, marca quanto já executou, tira da CPU e joga pra ready queue (reseta fatia de tempo)
// IF - Processo solicita IO, retira ele da CPU e aloca no dispositivo de IO,
// - SE O DISPotivo de IO tiver ocupado, espera na fila de dispositivos (IO/QUeue - Fila dupla encadeada, ordem de prioridade)

// Meta 1 - Fazer as filas. | Ready e Arrive = OK

Process* cpu(Process* p, int time_slice, int tempo_maximo){
    clock_t begin = clock();
    sleep(time_slice); 
    p->tam = p->tam - time_slice;
    return p;
}

void processa_ready(Ready* r, int time_slice, int tempo_maximo){
    Process* p = ready_retira(r);
    printf("Ready Depois de retirar P");
    ready_imprime(r);
    printf("Process ID: %d\nTAM ATUAL: %d\n", p->id, p->tam);
    p = cpu(p, time_slice, tempo_maximo);
    printf("TAM POS PROCESS: %d\n", p->tam);
    ready_insere(r, p);
    printf("depois de inserir p processado\n");
    ready_imprime(r);
    printf("\n");
}

void imprime_filas(Ready* r, Arrive* a, int time_slice, int tempo_maximo){
    for (int i = 0; i < 10; i++) {
        arrive_insere(a, rand());
        }
    arrive_imprime(a);
    printf("\nTransferindo de Arrive to Ready\n");
    arrive_to_ready(r, a);
    printf("\nReady Nova: \n");
    ready_imprime(r);
    printf("\nArrive Nova: \n");
    arrive_imprime(a);
    printf("\n");    
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: ./filename <NUM_MAX_DE_PROCESSOS\n");
        return 1;
    }
    Arrive* arrive_queue = arrive_cria();
    Ready* ready_queue = ready_cria();
    int tempo_maximo = 10;
    int time_slice = 2;

    printf("Estado atual de filas:");
    imprime_filas(ready_queue, arrive_queue, time_slice, tempo_maximo);
    processa_ready(ready_queue, time_slice, tempo_maximo);
    return 0;
}