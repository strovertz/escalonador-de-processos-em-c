#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Fila* r, Fila* a){
    Process* n = fila_retira(a);
    fila_insere_processo(r, n);
}

void* io_to_device(Lista* l, Fila* io){
    Process* p = ultimo(l);
    // Marca que esta fazendo io
    printf("dando bo aq1\n\n");
    fila_insere_processo(io, p);
    printf("dando bo aq2\n\n");
}