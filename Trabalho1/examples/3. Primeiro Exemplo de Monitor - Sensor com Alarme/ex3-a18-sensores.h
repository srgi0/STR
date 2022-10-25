/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		

*/


#ifndef		SENSORES_H
#define		SENSORES_H


#define LUGAR_0		0
#define LUGAR_1		1
#define LUGAR_2		2
#define N_LUGARES	3


/** Inicializa o monitor
*/
extern void sensores_init(void);


/**	Permite o registro da última medição obtida.
*/
extern void sensores_informa( int lugar, double medicao);


/** Permite ler a última medição do tipo solicitado. Caso a medição seja
mais do que 5 segundos velha, espera uma nova medição.
*/
extern double sensores_consulta( int lugar);


/** Bloqueia a thread chamadora até que as temperaturas em todos os lugares
fique acima de 100 graus.
*/
extern void sensores_espera100(void);



#endif		// SENSORES_H



