/*	LIVRO FUNDAMENTOS DOS SISTEMAS DE TEMPO REAL
*
*	Implementa uma tarefa periodica usando clock_nanosleep em modo absoluto
*	Compilar com:
*			gcc -o wcet wcet.c -lrt
*
*	Salva os tempos de execuÃ§Ã£o de uma tarefa
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define	NSEC_PER_SEC    (1000000000) 	// Numero de nanosegundos em um milissegundo

#define	N_AMOSTRAS	1000		// Numero de amostras (medicoes) coletadas

long temp_exec[N_AMOSTRAS];		// Medicoes do tempo de execuÃ§Ã£o da tarefaf em microsegundos


void bubble_sort (int vetor[], int n) {
 int contador, i, aux;
 for (contador = 1; contador < n; contador++) {
   for (i = 0; i < n - 1; i++) {
     if (vetor[i] > vetor[i + 1]) {
       aux = vetor[i];
       vetor[i] = vetor[i + 1];
       vetor[i + 1] = aux;
     }
   }
 }
}

int main(int argc, char* argv[])
{
	struct timespec t, t_inicio, t_fim;
	int amostra = 0;		// Amostra corrente
	int periodo = 100000000; 	// 100ms

	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);

	// Tarefa periodica iniciarÃ¡ em 1 segundo
	t.tv_sec++;
	
	srand(time(NULL));

	while(amostra < N_AMOSTRAS) {
		// Espera ateh inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
        // Realiza seu trabalho
		printf("Coletada a amostra %d\n", amostra);	
		
		//Gerar vetor
		int tam=100;
		int val[tam];
		for(int i=0;i<tam;i++)
			//val[i]= tam-i;
			val[i]= rand() % tam;
		
		// Le a hora atual, coloca em t_inicio
		clock_gettime(CLOCK_MONOTONIC ,&t_inicio);
		
		//ordena o array
		bubble_sort(val, tam);
		
		// Le a hora atual, coloca em t_fim
		clock_gettime(CLOCK_MONOTONIC ,&t_fim);

		// Calcula o tempo de execuÃ§Ã£o observado em microsegundos
		temp_exec[amostra++] = 1000000*(t_fim.tv_sec - t_inicio.tv_sec)   +   (t_fim.tv_nsec - t_inicio.tv_nsec)/1000;  	

		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC) {
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}
	}

	printf("\nMedicoes de Tempo de Execucao\n\n");
	
	FILE* dados_f;
	dados_f = fopen("dados_tempo_exec.txt", "w");
	if(dados_f == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);    
    }
	
	for( int i=0; i<N_AMOSTRAS; i++){
		//printf("Tempo de execucao=%4ldus\n", temp_exec[i]);
		fprintf(dados_f, "%4ld\n", temp_exec[i]);
	}
	
	fclose(dados_f);	

}
