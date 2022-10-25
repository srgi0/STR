/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		

		Mantem o saldo de uma conta bancária
*/


#ifndef		MONITORSALDOCONTA_H
#define		MONITORSALDOCONTA_H



/** Deposita 'valor' reais na conta bancária.
*/
extern void monitorsaldoconta_deposita( double valor);


/** Retira 'valor' reais da conta bancária, caso o saldo permita. Retorna 0 no sucesso e
	-1 na falha, quanto o saldo é insuficiente. Neste caso nenhum valor é retirado da conta.
*/
extern void monitorsaldoconta_retira( double valor);


/** Retorna o saldo atual da conta bancária.
*/
extern double monitorsaldoconta_lesaldo(void);



#endif		// MONITORSALDOCONTA_H


