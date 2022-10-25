/**		Rômulo Silva de Oliveira

		Programação Concorrente com Pthreads e Linguagem C

		

		Ilustra o uso de módulos na linguagem C.
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ex1-a18-saldoconta.h"


int main(void) {

	printf("Saldo inicial é %0.2lf\n", saldoconta_lesaldo() );
	
	saldoconta_deposita( 100.00 );

	printf("Saldo depois de depositar 100.00 é %0.2lf\n", saldoconta_lesaldo() );
	
	saldoconta_retira( 20.00 );
	
	printf("Saldo depois de retirar 20.00 é %0.2lf\n", saldoconta_lesaldo() );
		
	return 0;
}



