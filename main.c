#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "filas.h"
#include "untils.h"
clock_t begin;



// Processo é gerado e chega na arrive queue
// Tem espaço no Systema?  Tenta usar a CPU; Não tem ? espera na arrive até liberar.
// se a cpu estiver sendo utilizada Puxa pra Fila queue (FIFO)
// Senão, caso esteja livre, processa o time slice, 
// Não tem ? espera na arrive até liberar.

// Conseguiu a CPU? Executa até atender uma dessas condições:
// IF - Processo concluido, executa durante todo o tempo necessário pra conclusão dele
// Entra pra CPU o primeiro processo da fila de chegada, se n tiver processo na arrive, precisa puxar um gerador
// IF - Terminou a time slice, interrompe a execução do processo, marca quanto já executou, tira da CPU e joga pra ready queue (reseta fatia de tempo)
// IF - Processo solicita IO, retira ele da CPU e aloca no dispositivo de IO,
// - SE O DISPotivo de IO tiver ocupado, espera na fila de dispositivos (IO/QUeue - Fila dupla encadeada, ordem de prioridade)

// Meta 1 - Fazer as filas. | Fila e Fila = OK 
// Meta 2 - Implementar laço para ficar processando os proximos processos (ué kkk)

Process* cpu(Process* p, int time_slice, Lista *l){
    if(p->tam < time_slice) {
        usleep(p->tam);
        p->tam = 0;
        return p;
    } else usleep(time_slice);
    if(p->IO == 1)  {
        int t =rand()%100; 
        if(t > 50) {
            printf("[ETE %.1fs] Processo %d solicitou IO\n",  (double)(clock() - begin), p->id); 
            p->in_io = true;
            //lst_insere(l, p); 
            p->tam = p->tam - time_slice; 
            return p;
        }
    }
    p->tam = p->tam - time_slice;
    return p;
}

Process* io(Lista* l){

}


void processa_ready(Fila* r, Fila * a,  int time_slice, int tempo_maximo, Lista* l){
    Process* p = fila_retira(r);
    fila_imprime(r);
    printf("\n[ETE %.1fs] Process ID: %d\nQtd Slices: %d\n", (double)(clock() - begin),p->id, p->tam);
    if(p == NULL) {fila_insere_arrive(a); printf("[ETE %.1fs] Processo timido (nome e id desconhecidos ainda) chegou na fila Arrive com prioridade e tamanho\n", (double)(clock() - begin)); arrive_to_ready(r, a);}
    while (tempo_maximo != 0){      
        p = cpu(p, time_slice, l);
        if(p->tam > 0 && !p->in_io) {
            fila_insere_ready(r, p); 
            printf("[ETE %.1fs] Restam %d Slices para encerrar o processo %d\n", (double)(clock() - begin), p->tam, p->id);
        } else if (!p->in_io) { 
            printf("[ETE %.1fs] Processo %d encerrado\n", (double)(clock() - begin),p->id);
        } else printf("[ETE %.1fs] Processo %d em I/O\n",  (double)(clock() - begin), p->id); // Gerar Rand para caso caia em determinado numero processe a fila de i/o  
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
        printf("\n Tempo atual: ");
    }
    
}

void imprime_filas(Fila* r, Fila* a, int time_slice, int tempo_maximo){
    for (int i = 0; i < rand() %10; i++) {
        fila_insere_arrive(a);
        printf("[ETE %.1fs] Processo timido (nome e id desconhecidos ainda) chegou na fila Arrive com prioridade e tamanho\n", (double)(clock() - begin));
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
    //begin = clock();
    Fila* arrive_queue = fila_cria();
    Fila* ready_queue = fila_cria();
    Lista* io_queue = lst_cria();
    int tempo_maximo = 100;
    int time_slice = 2;
    
    printf("[ETE %.1fs] Filas Criadas, exibindo estado atual:\n", (double)(clock() - begin));
    imprime_filas(ready_queue, arrive_queue, time_slice, tempo_maximo);
    printf("\n [ETE %.1fs] -- INICIANDO PROCESSAMENTO --",(double)(clock() - begin));
    processa_ready(ready_queue, arrive_queue, time_slice, tempo_maximo, io_queue);
    return 0;
}