#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"

// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Fila* r, Fila* a){
    Process* n = fila_retira(a);
    fila_insere_ready(r, n);
    printf("\nTransferindo de Arrive to Ready\n");
}
