//Definição de Bibliotecas
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sensores.h"
#include "socket.h"
#include "tela.h"

#define	NSEC_PER_SEC    (1000000000) 	// Numero de nanosegundos em um segundo

void thread_mostra_status (void){
	double t, h;
	while(1){
		t = sensor_get("t");
		h = sensor_get("h");
		aloca_tela();
		system("tput reset");
		printf("---------------------------------------\n");
		printf("Temperatura (T)--> %.2lf\n", t);
		printf("Nivel (H)--> %.2lf\n", h);
		printf("---------------------------------------\n");
		libera_tela();
		sleep(1);	
	}	
		
}

void thread_le_sensor (void){ //Le Sensores periodicamente a cada 10ms
	struct timespec t;
	long periodo = 10e6; //10e6ns ou 10ms
	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);
	while(1){
		// Espera ateh inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		//Envia mensagem via canal de comunicação para receber valores de sensores
		sensor_put(socket_msg("st-0"), socket_msg("sh-0"));
		
		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC) {
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}					
	}
}

void thread_alarme (void){
	while(1){
		sensor_alarmeT(29);		
		aloca_tela();
		printf("ALARME\n");
		libera_tela();
		sleep(1);			
	}		
}


int main( int argc, char *argv[]) {
    
	socket_cria(argv[1], atoi(argv[2]) );
    
	pthread_t t1, t2, t3;
    
    pthread_create(&t1, NULL, (void *) thread_mostra_status, NULL);
    pthread_create(&t2, NULL, (void *) thread_le_sensor, NULL);
    pthread_create(&t3, NULL, (void *) thread_alarme, NULL);
    
	pthread_join( t1, NULL);
	pthread_join( t2, NULL);
	pthread_join( t3, NULL);
	    
	return 0;
}
