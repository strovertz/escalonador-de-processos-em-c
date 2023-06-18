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

// void trace(){
//     printf("a");
// }

Process* io(Lista* l, Fila* io){
    if(l->p == NULL) printf("aqui quebrou");
   
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
            printf("[ETE %.1fms] Processo %d solicitou IO %d\n",  (double)(clock() - begin), p->id, p->pr); 
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
    printf("\n[ETE %.1fms] Process ID: %d\nQtd Slices: %d\n", (double)(clock() - begin),p->id, p->tam);
    if(p == NULL) {fila_insere_arrive(a); printf("[ETE %.1fms]Sem Processos na Fila, Aguardando chegada", (double)(clock() - begin)); arrive_to_ready(r, a);}
    while (tempo_maximo != 0){      
        p = cpu(p, time_slice, l, io_queue);
        if(p->tam > 0 && !p->in_io) {
            fila_insere_processo(r, p); 
            printf("[ETE %.1fms] Restam %d Slices para encerrar o processo %d PR %d\n", (double)(clock() - begin), p->tam, p->id, p->pr);
        } else if (!p->in_io) { 
            printf("[ETE %.1fms] Processo %d encerrado\n", (double)(clock() - begin),p->id);
        } else printf("[ETE %.1fms] Processo %d em I/O\n",  (double)(clock() - begin), p->id); // Gerar Rand para caso caia em determinado numero processe a fila de i/o  
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
        printf("\n Tempo atual: ");
    }
    
}

void queue_init(Fila* r, Fila* a, int time_slice, int tempo_maximo){
    for (int i = 0; i < rand() %10; i++) {
        fila_insere_arrive(a);
        }
    fila_imprime(a);
    arrive_to_ready(r, a);
    printf("[ETE %.1fms]  Processo %d migrou para fila Ready\n", (double)(clock() - begin), r->ini->id);
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
    
    printf("[ETE %.1fms] Filas Criadas, exibindo estado atual:\n", (double)(clock() - begin));
    queue_init(ready_queue, arrive_queue, time_slice, tempo_maximo);
    printf("\n[ETE %.1fms] -- INICIANDO PROCESSAMENTO --",(double)(clock() - begin));
    processa_ready(ready_queue, arrive_queue, time_slice, tempo_maximo, io_queue);
    return 0;
}