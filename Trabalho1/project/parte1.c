#include <stdio.h>
#include <pthread.h>
#include <string.h>

int max (int arr[], int len){
    int max_value = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max_value){
            max_value = arr[i];
        }
    }
    return max_value;
}

#define N_TASKS 3
#define N_LINES N_TASKS+1

char menu_option[4] = {'0','0','0','0'};
char system_matrix[N_TASKS][3];

int P[N_LINES];
int C[N_LINES];
int D[N_LINES];

int system_period;


void print_system_matrix (void) {
    printf("--------\n");
    printf("\tP\tC\tD\n");
    for (int j=0; j<N_LINES; j++) {
        printf("T%d\t%d\t%d\t%d\n", j+1, P[j], C[j], D[j]);
    }
    printf("---------\n\n");
}

void RM (void) {
    printf("Rate Monotonic\n");
}

void DM (void) {
    printf("Deadline Monotonic\n");
}

void EDF (void) {
    printf("->Earliest Deadline First<-\n");
    printf("------. Escala de Tempo .------\n");


    
    for (int i = 0; i < N_TASKS; i++){
        printf("T%d ", i+1);
        for (int j = 0; j < system_period; j++){
            
        }
    }
}

int read_file (char system_file[]) {
    FILE *file_ptr = fopen(system_file, "r");
    rewind(file_ptr);
    
    /* 
    Assuming that system.txt has content in below format:
        P       C       D
        4       1       4
        5       2       5
        20      4       20
    */
    if (file_ptr == NULL) {
        printf("no such file.\n");
        return 0;
    }
    
    for (int i = 0; i < N_LINES; i++){
        fscanf(file_ptr, "%d %d %d ", &P[i], &C[i], &D[i]);
    }

    P[0] = 0;
    C[0] = 0;
    D[0] = 0;

    return 0;
}

int main(void) {
    system_period = max(P, sizeof P / sizeof *P);


    read_file("./sistemas/sistema1.txt");
    printf("%d\n",P[2]);
    
    print_system_matrix();

    while (strcmp(menu_option, "exit")) {
        printf("----------------------------------------------\n");
        printf("Escolha o Algoritmo de Escalonamento ou <exit> para sair:\n");
        printf("\t- <RM> (Rate Monotonic)\n");
        printf("\t- <DM> (Deadline Monotonic)\n");
        printf("\t- <EDF> (Earliest Deadline First)\n");
        printf("\t- <exit> (Sair do programa)\n");
        printf("--> ");
        scanf("%s", menu_option);

        if (!strcmp(menu_option, "RM")) {
            RM();
        } else
        if (!strcmp(menu_option, "DM")) {
            DM();
        } else
        if (!strcmp(menu_option, "EDF")){
            EDF();
        } else
        if (!strcmp(menu_option, "exit")){
            printf("Saindo...\n");
        }
        else {
            printf("Opcao invalida\n");
        }
    }

    







return(0);
}