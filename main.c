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
static int tempo_maximo;
static int turnarround_total;
static int qtd_proc;


void output() {
    FILE *text;
    text = fopen("outputFile.txt", "a"); // Abre o arquivo em modo de apêndice (append)

    if (text == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }
    fclose(text);
}

Process IO(){

}

Process* io(Lista* l, Fila* io, int tempo_maximo) {
    Process* p = ultimo(l);
    printf("Chegou aqui %d\n", tempo_atual);
    if (p == NULL) {
        printf("Problema com fila de IO\n");
    } else {
        io_to_device(p, io, tempo_atual);
        lst_imprime(l);
    }
    return io->ini;
}

Process* cpu(Process* p, int time_slice, Lista* l, Fila* io_device) {
    if (l->p != NULL && (rand()%20)) {
        io(); //constroi chamada
    }
    
    printf("%d\n", tempo_atual);
    
    if(p->IO == true) {
        if (rand()%2)
        {
            insere_crescente(&l, p);
            trace_print(tempo_atual, 7, p->id);
            return NULL;
        }
    }
    
    // printf("%d\n", tempo_atual);
    // if (p->IO == 1 /*&& (rand()%10) > 6*/) {
    //     printf("\nei\n");
    //     insere_crescente(&l, p);
    //     lst_imprime(l);
    //     fila_imprime(io_device);
    //     if (rand() % 100 > 75) {
    //         trace_print(tempo_atual, 8, p->id, p->pr);
    //         io(l, io_device, tempo_atual);
    //     }
    //     if (p->tam > time_slice){
    //         p->tam = p->tam - time_slice;
    //     } else {
    //         p->tam = p->tam - p->tam;
    //      }           
    //     return p;
    // }
    // if (p->tam < time_slice) {
    //     usleep(p->tam);
    //     p->tam = 0;
    //     tempo_atual = tempo_atual + p->tam;
    //     return p;
    // } else {
    //     usleep(time_slice);
    //     tempo_atual = tempo_atual + time_slice;
    // }
   //return p;
}

int processa_ready(Fila* r, Fila* a, int time_slice, Lista* l) {
    Fila* io_queue = fila_cria();
    Process* p = fila_retira(r);
    fila_imprime(r);
    trace_print(tempo_atual, 3, p->id, p->tam);
    if (p == NULL) {
        qtd_proc = fila_insere_arrive(a, tempo_atual, qtd_proc);
        trace_print(tempo_atual, 4, 0, 0);
        if(ml > ml_cnt)
            arrive_to_ready(r, a, tempo_atual);
        tempo_atual++;
    }
    while (tempo_atual < tempo_maximo) {
        p = cpu(p, time_slice, l, io_queue);
        printf("faco io ou nao %d\n", p->IO );
        if (p == NULL)
        {
            continue;
        }
        if (p->tam > 0) {
            printf("AGGGG");
            fila_insere_processo(r, p);
            trace_print(tempo_atual, 5, p->id, p->tam);
        } else {
            trace_print(tempo_atual, 6, p->id, 0);
            turnarround_total += (tempo_atual - p->queuetime);
            ml_cnt--;
        }
        if (rand() % 300 > 256 && ml_cnt < ml) {
            qtd_proc = fila_insere_arrive(a, tempo_atual, qtd_proc);
        }
        if (p->prox == NULL) {
            for (int i = 0; i < rand() % 10; i++) {
                if (ml_cnt < ml) {
                     qtd_proc = fila_insere_arrive(a, tempo_atual, qtd_proc);
                    arrive_to_ready(r, a, tempo_atual);
                } else {
                    printf("Processador esgotado, aguarde antes de inserir novos processos\n");
                }
            }
        }
        p = fila_retira(r);
        tempo_atual++;
    }
    if (tempo_atual >= tempo_maximo) {
        printf("\nTempo Máximo de Execução Alcançado\n");
        return -1;
    }
}

void queue_init(Fila* r, Fila* a, int time_slice) {
    for (int i = 0; i < rand() % 10; i++) {
        if(i!=0) tempo_atual+=rand()%2;
         qtd_proc = fila_insere_arrive(a, tempo_atual, qtd_proc);
        ml_cnt++;
    }
    fila_imprime(a);
    if(arrive_to_ready(r, a, tempo_atual) == -1) return;
    fila_imprime(r);
    printf("\n");
    tempo_atual++;
}

int main(int argc, char* argv[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE* text;
    text = fopen("traceFile.txt", "a"); // Abre o arquivo em modo de apêndice (append)

    Fila* arrive_queue = fila_cria();
    Fila* ready_queue = fila_cria();
    Lista* io_queue = lst_cria();

    int rr;

    trace_print(tempo_maximo, 1, 0, 0);

    FILE* arquivo_entrada = fopen("inputFile.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    fscanf(arquivo_entrada, "%d", &tempo_maximo);
    fscanf(arquivo_entrada, "%d", &ml);
    fscanf(arquivo_entrada, "%d", &rr);
    fprintf(text, "::::::::::::::New Simulation::::::::::::::\n    ***Date: %d-%02d-%02d %02d:%02d:%02d***\n     ***ST: %d, ML: %d, RR: %d ***\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tempo_atual, ml_cnt, rr);

    tempo_maximo = tempo_maximo;

    fclose(text);
    fclose(arquivo_entrada);
    tempo_atual++;
    queue_init(ready_queue, arrive_queue, rr);
    trace_print(tempo_atual, 2, 0, 0);
    processa_ready(ready_queue, arrive_queue, rr, io_queue);
    printf("turn arround media: %d\n", turnarround_total/qtd_proc);
    fila_libera(arrive_queue);
    fila_libera(ready_queue);
    lst_desaloca(io_queue);

    return 0;
}
