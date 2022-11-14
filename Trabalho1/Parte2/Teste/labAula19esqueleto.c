//Definição de Bibliotecas
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define	NSEC_PER_SEC    (1000000000) 	// Numero de nanosegundos em um segundo

void thread_mostra_status (void){
	
	while(1){
							
	}	
		
}

void thread_le_sensor (void){ //Le Sensores periodicamente a cada 10ms
	
	while(1){
				
	}		
}

void thread_alarme (void){
	
	while(1){
			
	}
		
}

///Controle
void thread_controle_temperatura (void){
			
	while(1){			
					
	}
}

void thread_grava_temp_resp(void){
	
	while(1){
							
	}	
	
}

void main( int argc, char *argv[]) {
    ref_putT(29.0);
	cria_socket(argv[1], atoi(argv[2]) );
    
	pthread_t t1, t2, t3, t4, t5;
    
    pthread_create(&t1, NULL, (void *) thread_mostra_status, NULL);
    pthread_create(&t2, NULL, (void *) thread_le_sensor, NULL);
    pthread_create(&t3, NULL, (void *) thread_alarme, NULL);
    pthread_create(&t4, NULL, (void *) thread_controle_temperatura, NULL);
    pthread_create(&t5, NULL, (void *) thread_grava_temp_resp, NULL);
    
	pthread_join( t1, NULL);
	pthread_join( t2, NULL);
	pthread_join( t3, NULL);
	pthread_join( t4, NULL);
	pthread_join( t5, NULL);
	    
}