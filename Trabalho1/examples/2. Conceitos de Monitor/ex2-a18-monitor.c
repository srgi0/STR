/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "ex2-a18-monitorsaldoconta.h"


#define	N_THREADS	4

static pthread_t th_deposita[N_THREADS];	// Identificadores das threads que depositam
static pthread_t th_retira[N_THREADS];		// Identificadores das threads que retiram



/** Faz 10 depositos de 20 reais a cada 1 segundo */
static void codigo_tarefa_deposita(void){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Vai depositar 20.00 reais\n");
		monitorsaldoconta_deposita(20.00);
		printf("Depositou 20.00 reais\n");
	}
}


/** Faz 10 retiradas de 20 reais a cada 1 segundo */
static void codigo_tarefa_retira(void){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Vai retirar 20.00 reais\n");
		monitorsaldoconta_retira(20.00);
		printf("Retirou 20.00 reais\n");
	}
}



/** Função principal, cria as threads */
int main(void){
	printf("Inicio\n");
	printf("Saldo inicial %0.2lf\n", monitorsaldoconta_lesaldo() );

	// Cria todas as threads que retiram
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&th_retira[i], NULL, (void *) codigo_tarefa_retira, NULL);

	// Cria todas as threads que depositam
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&th_deposita[i], NULL, (void *) codigo_tarefa_deposita, NULL);

	// Espera por todas as threads que retiram
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(th_retira[i], NULL);

	// Espera por todas as threads que depositam
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(th_deposita[i], NULL);

	printf("Saldo final ficou %0.2lf\n", monitorsaldoconta_lesaldo() );

	printf("Fim\n");
	return(0);
}





