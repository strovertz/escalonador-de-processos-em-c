typedef struct lista{
	int info;
	struct lista* ant;
	struct lista* prox;
}Lista;


Lista* lst_cria(void);
Lista* lst_insere(Lista* l, int v);
Lista* ultimo (Lista* l);
Lista* lst_retira_ant (Lista* l, int v);
Lista* lst_busca(Lista* l, int v);
void lst_imprime(Lista *l);
void lst_desaloca(Lista* l);	

