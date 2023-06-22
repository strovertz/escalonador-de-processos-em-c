// Código 1
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "filas.h"
#include "untils.h"

clock_t begin;

static int ml_cnt;
static int ml;
static int tempo_atual;
static int max_time;

Process* io(Lista* l, Fila* io, int tempo_maximo) {
    // if (l->p == NULL) {
    //     trace_print(tempo_atual,0, 0, 0);
    //     return NULL;
    //     }
    if (io->ini == NULL && io->fim == NULL) {
        io = io_to_device(l, io, tempo_atual);
        lst_imprime(l);
    }
    if (rand() % 100 > 75) {
        io->ini->in_io = true;

    }
    return io->ini;
}

Process* cpu(Process* p, int time_slice, Lista* l, Fila* io_device) {
    printf("%d\n", tempo_atual);
    if (p->tam < time_slice) {
        usleep(p->tam); 
        p->tam = 0;
        tempo_atual = tempo_atual+p->tam;
        return p; 
    } else {  
        usleep(time_slice);
        tempo_atual = tempo_atual+time_slice;
    }
    if (p->IO == 1) {
        if (rand() % 100 > 75) {
            trace_print(tempo_atual,8, p->id, p->pr);
            l = insere_crescente(l, p);
            lst_imprime(l);
            if (rand() % 100 > 75) {
                io(l, io_device, tempo_atual);
                return p; // retorna sem decrementar a time slice
            }
            p->tam = p->tam - time_slice;
            return p;
        }
    }
    p->tam = p->tam - time_slice;
    return p;
}

void processa_ready(Fila* r, Fila* a, int time_slice, int tempo_maximo, Lista* l) {
    Fila* io_queue = fila_cria();
    Process* p = fila_retira(r);
    fila_imprime(r);
    trace_print(tempo_atual,3, p->id, p->tam);
    if (p == NULL && ml_cnt < ml) {
        fila_insere_arrive(a, tempo_atual);
        trace_print(tempo_atual,4, 0, 0);
        arrive_to_ready(r, a, tempo_atual);
        tempo_atual++;
    }
        while (tempo_atual != tempo_maximo) {
        p = cpu(p, time_slice, l, io_queue);
        if (p->tam > 0 && !p->in_io) {
            fila_insere_processo(r, p);
            trace_print(tempo_atual,5, p->id, p->tam);
        } else if (!p->in_io) {
            trace_print(tempo_atual,6, p->id, 0);
            ml_cnt--;
        } else {
            trace_print(tempo_atual,7, p->id, 0);
        }
        if (rand() % 300 > 256 &&  ml_cnt < ml) {
            fila_insere_arrive(a, tempo_atual);
        }
        if (p->prox == NULL) {
            for (int i = 0; i < rand() % 10; i++) {
                if(ml_cnt < ml){
                    fila_insere_arrive(a, tempo_atual);
                    arrive_to_ready(r, a, tempo_atual);
                } else printf("Processador esgotado, aguarde antes de inserir novos processos");
            }
        }
        p = fila_retira(r);
        tempo_atual++;
         if (tempo_atual == tempo_maximo) {
            printf("\nTempo Máximo de Execução Alcançado\n");
       }
    }
    if (tempo_atual == tempo_maximo) {
        printf("\nTempo Máximo de Execução Alcançado\n");
    }
}

void queue_init(Fila* r, Fila* a, int time_slice, int tempo_maximo) {
    for (int i = 0; i < rand() % 10; i++) {
        fila_insere_arrive(a, tempo_maximo);
        ml_cnt++;
    }
    fila_imprime(a);
    arrive_to_ready(r, a, tempo_maximo);
    fila_imprime(r);
    printf("\n");
    tempo_atual++;
}

int main(int argc, char* argv[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *text;
    text = fopen("traceFile.txt", "a"); // Abre o arquivo em modo de apêndice (append)

    Fila* arrive_queue = fila_cria();
    Fila* ready_queue = fila_cria();
    Lista* io_queue = lst_cria();

    int tempo_maximo;
    int rr;
    
    trace_print(tempo_maximo,1, 0, 0);

    FILE* arquivo_entrada = fopen("inputFile.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    fscanf(arquivo_entrada, "%d", &tempo_maximo);
    fscanf(arquivo_entrada, "%d", &ml);
    fscanf(arquivo_entrada, "%d", &rr);
    fprintf(text, "::::::::::::::New Simulation::::::::::::::\n    ***Date: %d-%02d-%02d %02d:%02d:%02d***\n     ***ST: %d, ML: %d, RR: %d ***\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,tempo_atual,ml_cnt,rr);
   
    tempo_maximo = tempo_maximo*(-1);

    fclose(text);
    fclose(arquivo_entrada);
    tempo_atual++;
    queue_init(ready_queue, arrive_queue, rr, tempo_maximo);
    trace_print(tempo_maximo,2, 0, 0);
    processa_ready(ready_queue, arrive_queue, rr, tempo_maximo, io_queue);

    return 0;
}
