/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		
*/		


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define	N_THREADS	10

pthread_t minhas_threads[N_THREADS];		// Identificadores para 10 threads


/** Espera passar *nst segundos, de segundo em segundo */
void codigo_tarefa(int *nst){
	for( int ns=0; ns < *nst; ++ns) {
		sleep(1);
		printf("Tarefa: passaram %d segundos do total de %d.\n", ns+1, *nst);
	}
}


/** Função principal, cria as threads */
int main(void){
	int param_threads[N_THREADS];

	printf("Inicio\n");

	// Prepara os parametros de todas as threads
	for( int i=0; i<N_THREADS; ++i)
		param_threads[i] = 5+i;

	// Cria todas as threads
	for( int i=0; i<N_THREADS; ++i)
		pthread_create(&minhas_threads[i], NULL, (void *) codigo_tarefa, (void *)&param_threads[i]);

	// Espera por todas as threads
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(minhas_threads[i], NULL);

	printf("Fim\n");
	return(0);
}



