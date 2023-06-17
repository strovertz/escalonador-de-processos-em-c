// Necessidades do processo: 
// 1. ID
// 2. Tamanho (Qtd de Tempo que precisa rodar, definido por qntdtempo_emsegundo/tam_timeslice)
// 3. Time stamp pra cada uma das filas, inicialmente guarda o horario qe entrou na fila, quando sair, guarda a diferença de inicio e fim, assim vai ter o tempo total na fila
// 4.  Faz IO? Rand 1/0

typedef struct lista{
	int id;
    int tam;
    int queuetime;
    bool IO;
    int pr;
	struct lista* prox;
}Process;

// typedef struct Fila{
// 	Process* ini;
// 	Process* fim;
// }Fila;

typedef struct Fila{
    Process* ini;
    Process* fim;
}Fila;

Fila* fila_cria(void);
int fila_tam(Fila* f);
void fila_insere_arrive(Fila* f);
// Process* Fila_retira(Fila* f);
// void Fila_imprime(Fila* f);
// int Fila_vazia(Fila* f);
// void Fila_libera(Fila* f);

//Fila* Fila_cria(void);
// int Fila_tam(Fila * f);
void fila_insere_ready(Fila* f, Process* n);
// Process* Fila_retira(Fila* f);
// void Fila_imprime(Fila* f);
// int Fila_vazia(Fila* f);
// void Fila_libera(Fila* f);