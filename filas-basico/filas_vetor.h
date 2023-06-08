#define N 4

typedef struct fila_vetor{
	int n;
	int ini;
	int* vet;
}Fila_vetor;

Fila_vetor* filaVetor_cria(void);
void filaVetor_insere(Fila_vetor* f, int valor);
int filaVetor_retira(Fila_vetor* f);
void filaVetor_imprime(Fila_vetor* f);
int filaVetor_vazia(Fila_vetor* f);
void filaVetor_libera(Fila_vetor* f);