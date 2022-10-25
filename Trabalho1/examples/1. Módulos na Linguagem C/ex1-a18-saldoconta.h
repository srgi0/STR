/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		

		Mantem o saldo de uma conta bancária
*/


#ifndef		SALDOCONTA_H
#define		SALDOCONTA_H



/** Deposita 'valor' reais na conta bancária.
*/
extern void saldoconta_deposita( double valor);


/** Retira 'valor' reais da conta bancária, caso o saldo permita. Retorna 0 no sucesso e
	-1 na falha, quanto o saldo é insuficiente. Neste caso nenhum valor é retirado da conta.
*/
extern int saldoconta_retira( double valor);


/** Retorna o saldo atual da conta bancária.
*/
extern double saldoconta_lesaldo(void);



#endif		// SALDOCONTA_H


