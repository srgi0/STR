/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "ex3-a18-sensores.h"



#define	N_THREADS	6

static pthread_t th_informa[N_THREADS];		// Identificadores das threads que informam
static pthread_t th_consulta[N_THREADS];		// Identificadores das threads que consultam
static pthread_t th_espera[N_THREADS];			// Identificadores das threads que esperam


/** Faz 20 informes, um por segundo */
static void codigo_tarefa_informa(int *plugar) {
	for( int i=0; i<20; ++i) {
		sleep(1);
		printf("Vai informar lugar %d medicao %d\n", *plugar, i*10);
		sensores_informa( *plugar, i*10);
	}
}


/** Faz 20 consultas, uma por segundo */
static void codigo_tarefa_consulta(int *plugar) {
	double lido;
	for( int i=0; i<20; ++i) {
		sleep(1);
		lido = sensores_consulta(*plugar);
		printf("Consultou o lugar %d, tem medicao %.0lf\n", *plugar, lido);
	}
}


/** Espera todas as medicoes passarem de 100 */
static void codigo_tarefa_espera(void) {
	printf("Vai esperar todos100\n");
	sensores_espera100();
	printf("Retornou de todos100\n");
}




/** Função principal, cria as threads */
int main(void){
	int lugares[] = { LUGAR_0, 1, 2, 0, 1, 2};
	printf("Inicio\n");
	
	// Inicializa o monitor
	sensores_init();


	// Cria threads para consultar medicoes
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&th_consulta[i], NULL, (void *) codigo_tarefa_consulta, (void *)&lugares[i]);
	sleep(1);	// Deixa eles esperando por novas medições

	// Cria threads para informar medicoes
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&th_informa[i], NULL, (void *) codigo_tarefa_informa, (void *)&lugares[i]);

	// Cria threads para esperar todas100
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&th_espera[i], NULL, (void *) codigo_tarefa_espera, NULL);


	// Espera por todas as threads que informam
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(th_informa[i], NULL);

	// Espera por todas as threads que consultam
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(th_consulta[i], NULL);

	// Espera por todas as threads que esperam
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(th_espera[i], NULL);

	// Medicoes finais
	printf("Medicoes finais, lugar0=%lf, lugar1=%lf, lugar2=%lf\n", 
				sensores_consulta(0), sensores_consulta(1), sensores_consulta(2) );

	printf("Fim\n");
	return(0);
}





