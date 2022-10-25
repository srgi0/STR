/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		

		Mantem o saldo de uma conta bancária
*/


#include <stdio.h>
#include <stdlib.h>

#include "ex1-a18-saldoconta.h"


static double saldo = 0.0;		// Conta inicia com saldo zero


/** Deposita 'valor' reais na conta bancária.
*/
void saldoconta_deposita( double valor) {
	saldo += valor;
}	


/** Retira 'valor' reais da conta bancária, caso o saldo permita. Retorna 0 no sucesso e
	-1 na falha, quanto o saldo é insuficiente. Neste caso nenhum valor é retirado da conta.
*/
int saldoconta_retira( double valor) {
	if( saldo < valor )
		return -1;
	saldo -= valor;
	return 0;
}	


/** Retorna o saldo atual da conta bancária.
*/
double saldoconta_lesaldo(void) {
	return saldo;
}	





