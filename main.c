#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

// Meta 1 - Fazer as filas.

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: ./filename <NUM_MAX_DE_PROCESSOS\n");
        return 1;
    }
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
    return 0;
}