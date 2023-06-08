typedef struct lista{
	int info;
	struct lista* prox;
}Lista;

typedef struct fila_lista{
	Lista* ini;
	Lista* fim;
}Fila_lista;


Fila_lista* filaLista_cria(void);
void filaLista_insere(Fila_lista* f, int valor);
int filaLista_retira(Fila_lista* f);
void filaLista_imprime(Fila_lista* f);
int filaLista_vazia(Fila_lista* f);
void filaLista_libera(Fila_lista* f);