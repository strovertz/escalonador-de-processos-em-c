// função que tira da fila Arrive q joga pra fila Ready
void* arrive_to_ready(Fila* r, Fila* a);
void* io_to_device(Lista* l, Fila* io);
void trace_print(int selector,int process_id, int utils);