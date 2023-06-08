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
	struct lista* prox;
}Process;

typedef struct arrive{
	Process* ini;
	Process* fim;
}Arrive;

typedef struct ready{
    Process* ini;
    Process* fim;
}Ready;

Arrive* arrive_cria(void);
void arrive_insere(Arrive* f, int valor);
Process* arrive_retira(Arrive* f);
void arrive_imprime(Arrive* f);
int arrive_vazia(Arrive* f);
void arrive_libera(Arrive* f);

Ready* ready_cria(void);
void ready_insere(Ready* f, Process* n);
Process* ready_retira(Ready* f);
void ready_imprime(Ready* f);
int ready_vazia(Ready* f);
void ready_libera(Ready* f);