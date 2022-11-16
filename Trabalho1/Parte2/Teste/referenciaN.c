/* Monitor sensor, no arquivo sensor.c */ 
#include <math.h>
#include <pthread.h>

static pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER; 
static double ref_entrada_N = 0;

/* Chamado pela thread que le o sensor e disponibiliza aqui o valor lido */
 void ref_putN( double ref) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 ref_entrada_N = ref; 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor */ 
 double ref_getN( void) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 aux = ref_entrada_N; 
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux;
 }
