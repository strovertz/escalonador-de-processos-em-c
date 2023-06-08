#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
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

void teste(int time_slice, int tempo_maximo){
    Arrive* arrive_queue = arrive_cria();
    Ready* ready_queue = ready_cria();
    for (int i = 0; i < 10; i++) {
        arrive_insere(arrive_queue, rand());
        }
    arrive_imprime(arrive_queue);
    printf("\nTRANFERINDO DE ARRIVE TO READY\n");
    arrive_to_ready(ready_queue, arrive_queue);
    printf("\nREADY NOVA: \n");
    ready_imprime(ready_queue);
    printf("\nARRIVE NOVA: \n");
    arrive_imprime(arrive_queue);
    printf("\n");
    printf("TESTANDO PROCESSADOR\n");
    Process* p = ready_retira(ready_queue);
    printf("TAM ATUAL: %d\n", p->tam);
    p = cpu(p, time_slice, tempo_maximo);
    printf("TAM POS PROCESS: %d", p->tam);
    ready_insere(ready_queue, p);
    printf("\n");

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: ./filename <NUM_MAX_DE_PROCESSOS\n");
        return 1;
    }
    int tempo_maximo = 10;
    int time_slice = 20;
    teste(time_slice, tempo_maximo);
    return 0;
}