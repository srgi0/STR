/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		
*/		


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t t1;	// Identificador da thread t1
pthread_t t2;	// Identificador da thread t2 

int ERRO_TH = 111;		// Codigo que indica erro na thread
int SUCESSO_TH = 222; 	// Codigo que indica sucesso na thread


/** Espera passar 10 segundos, de segundo em segundo */
void *codigo_tarefa_1(void){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Tarefa 1: passaram %d segundos\n", ns+1);
	}
	return( (void *) &SUCESSO_TH);
}


/** Espera passar 15 segundos, de segundo em segundo */
void codigo_tarefa_2(void){
	for( int ns=0; ns < 15; ++ns) {
		sleep(1);
		printf("Tarefa 2: passaram %d segundos\n", ns+1);
	}
	pthread_exit(&ERRO_TH);
}


/** Função principal, cria as threads */
int main(void){
	int *retorno_t1;	// Codigo de termino da thread 1
	int *retorno_t2;	// Codigo de termino da thread 2
	
	printf("Inicio\n");

	pthread_create(&t1, NULL, (void *) codigo_tarefa_1, NULL);
	pthread_create(&t2, NULL, (void *) codigo_tarefa_2, NULL);

	pthread_join(t1, (void **) &retorno_t1);
	pthread_join(t2, (void **) &retorno_t2);

	printf("Fim: t1 retornou %d, t2 retornou %d\n", *retorno_t1, *retorno_t2);
	return(0);
}



