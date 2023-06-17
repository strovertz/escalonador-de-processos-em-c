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
    bool in_io;
    int pr;
	struct lista* prox;
}Process;

typedef struct Fila{
    Process* ini;
    Process* fim;
}Fila;

typedef struct list{
	int pr;
    Process* p;
    struct list* ini;
	struct list* ant;
	struct list* prox;
}Lista;

Lista* lst_cria(void);
Lista* lst_insere(Lista* l, Process* p);
Lista* ultimo (Lista* l);
Lista* lst_retira_ant (Lista* l, int v);
Lista* insere_crescente(Lista* l, Process* proc);
Lista* lst_busca(Lista* l, int v);
void lst_imprime(Lista *l);
void lst_desaloca(Lista* l);	



Fila* fila_cria(void);
int fila_tam(Fila* f);
void fila_insere_ready(Fila* f, Process* n);
void fila_insere_arrive(Fila* f);
Process* fila_retira(Fila* f);
void fila_imprime(Fila* f);
int fila_vazia(Fila* f);
void fila_libera(Fila* f);