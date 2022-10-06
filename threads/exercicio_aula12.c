#include <stdio.h>

#include <ctype.h>      // para função isupper()
#include <unistd.h>     // para função sleep()
#include <pthread.h>    // para utilizar a API de threads

#include <string.h>     // usar mais facilmente strings


int SUCCESS_CODE = 100;
int ERROR_CODE = 111;

#define NUMBER_OF_THREADS    5
#define MAX_NAME_SIZE   20

pthread_t threads_vector[NUMBER_OF_THREADS];

char threads_names_vector[NUMBER_OF_THREADS][MAX_NAME_SIZE] =
{ "Thread",
  "tarefa",
  "thread",
  "Tarefa",
  "a"
};


void threads_code (char thread_name[MAX_NAME_SIZE]){
    for (int i=0; i<10; ++i){
        /*
        count++ is post increment where ++count is pre increment. suppose you write count++ means value
        increase after execute this statement. But in case ++count value will increase while executing this line.
        */
        sleep(1);
        printf("Passaram-se %d segundos\n", i+1);
    }


    if (isupper(thread_name[0]))
        pthread_exit(&SUCCESS_CODE);
    else
        pthread_exit(&ERROR_CODE);
}

int main (void) {
    int *return_thread[NUMBER_OF_THREADS];

    for (int i=0; i<NUMBER_OF_THREADS; i++)
        pthread_create(&threads_vector[i], NULL, (void *) threads_code, (void *) &threads_names_vector[i]);
    

    for (int i=0; i<NUMBER_OF_THREADS; i++)
        pthread_join(threads_vector[i], (void **) &return_thread[i]);


    for (int i=0; i<NUMBER_OF_THREADS; i++)
        printf("Return code for Thread %d is %d\n", i, *return_thread[i]);

return(0);
}