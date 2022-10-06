/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		
*/		


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


/* Estrutura para passar parametros para uma thread */
struct param_t {
	int nst;		// Numero de segundos no total
	char *nome;		// Nome da thread
};
	

pthread_t t1;	// Identificador da thread t1
pthread_t t2;	// Identificador da thread t2 



/** Espera passar pparam->nst segundos, de segundo em segundo */
void codigo_tarefa_1(struct param_t *pparam){
	for( int ns=0; ns < pparam->nst; ++ns) {
		sleep(1);
		printf("%s: passaram %d segundos\n", pparam->nome, ns+1);
	}
}



/** Espera passar *nst segundos, de segundo em segundo */
void codigo_tarefa_2(int *nst){
	for( int ns=0; ns < *nst; ++ns) {
		sleep(1);
		printf("Tarefa 2: passaram %d segundos\n", ns+1);
        }
}


/** Função principal, cria as threads */
int main(void){
	struct param_t param1;
	int param2;
	
	// Parametros para a thread 1
	param1.nst = 5;
	param1.nome = "TAREFA 1"; 	
	
	// Parametros para a thread 2
	param2 = 15;

	printf("Inicio\n");

	pthread_create(&t1, NULL, (void *) codigo_tarefa_1, (void *) &param1);
	pthread_create(&t2, NULL, (void *) codigo_tarefa_2, (void *) &param2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Fim\n");
	return(0);
}


