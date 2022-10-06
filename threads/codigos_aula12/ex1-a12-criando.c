/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		
*/		


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t t1;	// Identificador da thread t1
pthread_t t2;	// Identificador da thread t2 


/** Espera passar 10 segundos, de segundo em segundo */
void codigo_tarefa_1(void){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Tarefa 1: passaram %d segundos\n", ns+1);
	}
}


/** Espera passar 15 segundos, de segundo em segundo */
void codigo_tarefa_2(void){
	for( int ns=0; ns < 15; ++ns) {
		sleep(1);
		printf("Tarefa 2: passaram %d segundos\n", ns+1);
	}
}


/** Função principal, cria as threads */
int main(void){
	printf("Inicio\n");

	pthread_create(&t1, NULL, (void *) codigo_tarefa_1, NULL);
	pthread_create(&t2, NULL, (void *) codigo_tarefa_2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Fim\n");
	return(0);
}



