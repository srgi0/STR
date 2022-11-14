/* Monitor sensor, no arquivo sensor.c */ 
#include <math.h>
#include <pthread.h>
#include <string.h>

static pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 
static double s_temp = 0, s_nivel = 0, s_Ta = 0, s_Ti = 0, s_No = 0;
static double limite_atual = HUGE_VAL;

/* Chamado pela thread que le o sensor e disponibiliza aqui o valor lido */
 void sensor_put( double temp, double nivel) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 s_temp = temp;
	 s_nivel = nivel;
	 if( s_temp >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }

 void sensor_put2(double Ta, double Ti, double No) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 s_Ta = Ta;
	 s_Ti = Ti;
	 s_No = No;
	 pthread_mutex_unlock( &exclusao_mutua); 
 }

 
 /* Chamado por qualquer thread que precisa do valor lido do sensor */ 
 double sensor_get(char s[2]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 if (strncmp(s,"t",2)==0)
	 aux = s_temp;
	 else if(strncmp(s,"h",2)==0)
	 aux = s_nivel;
	 else if(strncmp(s,"ti",2)==0)
	 aux = s_Ti;
	 else if(strncmp(s,"ta",2)==0)
	 aux = s_Ta;
	 else if(strncmp(s,"no",2)==0)
	 aux = s_No;
	 pthread_mutex_unlock( &exclusao_mutua);
	 return aux;
 }

/* Thread fica bloqueada até o valor do sensor chegar em limite */ 
void sensor_alarmeT( double limite) {
	pthread_mutex_lock( &exclusao_mutua); 
	limite_atual = limite; 
	while( s_temp < limite_atual) 
		pthread_cond_wait( &alarme, &exclusao_mutua); 
	limite_atual = HUGE_VAL; 
	pthread_mutex_unlock( &exclusao_mutua); 
}
