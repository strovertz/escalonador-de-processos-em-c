#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"

// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Ready* r, Arrive* a){
    Process* n = arrive_retira(a);
    ready_insere(r, n);
}
