/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		s05-a25-sensores.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#include "ex3-a18-sensores.h"


struct dados_medidos_t {
	time_t hora;
	double valor;
};

static pthread_mutex_t em = PTHREAD_MUTEX_INITIALIZER;

static struct dados_medidos_t medicoes[N_LUGARES];
static int inicializado = 0;	// 1 indica que o monitor foi inicializado


static pthread_cond_t todos100 = PTHREAD_COND_INITIALIZER;	// Espera por todas as medicoes acima de 100

static pthread_cond_t tem_medicao_lugar0 = PTHREAD_COND_INITIALIZER;	// Espera por medicao no LUGAR_0
static pthread_cond_t tem_medicao_lugar1 = PTHREAD_COND_INITIALIZER;	// Espera por medicao no LUGAR_1
static pthread_cond_t tem_medicao_lugar2 = PTHREAD_COND_INITIALIZER;	// Espera por medicao no LUGAR_2



/** Inicializa o monitor
*/
void sensores_init(void) {
	pthread_mutex_lock(&em);	
	if( inicializado == 0 ) {
		for( int i=0; i<N_LUGARES; ++i) {
			medicoes[i].hora = 0;	// 1/jan/1970, bem velho
			medicoes[i].valor = 0;
		}
		inicializado = 1;
	}
	pthread_mutex_unlock(&em);	
}


/**	Permite o registro da última medição obtida.
*/
void sensores_informa( int lugar, double medicao) {
	pthread_mutex_lock(&em);
	printf("sensores_informa: lugar %d medicao %.0lf\n", lugar, medicao);
	medicoes[lugar].hora = time(NULL);
	medicoes[lugar].valor = medicao;

	// Sinaliza caso alguém esteja esperando medição
	if( lugar == LUGAR_0 )
		pthread_cond_broadcast(&tem_medicao_lugar0);
	if( lugar == LUGAR_1 )
		pthread_cond_broadcast(&tem_medicao_lugar1);
	if( lugar == LUGAR_2 )
		pthread_cond_broadcast(&tem_medicao_lugar2);

	// Sinaliza se todas as medições são maiores que 100
	if(  medicoes[LUGAR_0].valor > 100.0  &&
			medicoes[LUGAR_1].valor > 100.0	&&
			medicoes[LUGAR_2].valor > 100.0	) {
		pthread_cond_broadcast(&todos100);
	}
	pthread_mutex_unlock(&em);	
}


/** Permite ler a última medição do tipo solicitado. Caso a medição seja
mais do que 5 segundos velha, espera uma nova medição.
*/
double sensores_consulta( int lugar) {
	double retorno;
	time_t agora, idade;

	pthread_mutex_lock(&em);
	agora = time(NULL);
	idade = difftime( agora, medicoes[lugar].hora );
	printf("sensores_consulta: lugar %d idade %ld\n", lugar, idade);
	while( idade > 5 ) {
		if( lugar == LUGAR_0 )
			pthread_cond_wait(&tem_medicao_lugar0, &em);	// Espera medição do lugar certo
		else if( lugar == LUGAR_1 )
			pthread_cond_wait(&tem_medicao_lugar1, &em);
		else if( lugar == LUGAR_2 )
			pthread_cond_wait(&tem_medicao_lugar2, &em);

		agora = time(NULL);
		idade = difftime( agora, medicoes[lugar].hora );
		printf("sensores_consulta acordou: lugar %d idade %ld\n", lugar, idade);
	}
	retorno = medicoes[lugar].valor;
	pthread_mutex_unlock(&em);	
	return retorno;
}


/** Bloqueia a thread chamadora até que as temperaturas em todos os lugares
fique acima de 100 graus.
*/
void sensores_espera100(void) {
	pthread_mutex_lock(&em);

	while(  medicoes[LUGAR_0].valor < 100.0	||
			medicoes[LUGAR_1].valor < 100.0	||
			medicoes[LUGAR_2].valor < 100.0	) {

		pthread_cond_wait(&todos100, &em);
	}	

	pthread_mutex_unlock(&em);	
}



