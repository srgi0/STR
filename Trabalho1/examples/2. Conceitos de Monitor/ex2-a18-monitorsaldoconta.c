/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		

		Mantem o saldo de uma conta bancária
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ex2-a18-monitorsaldoconta.h"


static double saldo = 0.0;		// Conta inicia com saldo zero


static pthread_mutex_t em = PTHREAD_MUTEX_INITIALIZER;		// Garante exclusão mútua no monitor

static pthread_cond_t tem_saldo = PTHREAD_COND_INITIALIZER;	// Espera pelo saldo necessário



/** Deposita 'valor' reais na conta bancária.
*/
void monitorsaldoconta_deposita( double valor) {
	pthread_mutex_lock(&em);	
	saldo += valor;
	pthread_cond_broadcast(&tem_saldo);		// Sinaliza que tem algum saldo
	pthread_mutex_unlock(&em);	
}	


/** Retira 'valor' reais da conta bancária, caso o saldo permita. Fica bloqueado até que exista 
	saldo suficiente.
*/
void monitorsaldoconta_retira( double valor) {
	pthread_mutex_lock(&em);	
	while( saldo < valor )
		pthread_cond_wait(&tem_saldo, &em);	// Espera por saldo		
	saldo -= valor;
	pthread_mutex_unlock(&em);	
}	


/** Retorna o saldo atual da conta bancária.
*/
double monitorsaldoconta_lesaldo(void) {
	double aux;
	pthread_mutex_lock(&em);	
	aux = saldo;
	pthread_mutex_unlock(&em);			
	return aux;
}	





