#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

int max (int arr[], int len){
    int max_value = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max_value){
            max_value = arr[i];
        }
    }
    return max_value;
}

// ------------------------------------------------------------------------------------

#define N_TASKS 3
#define N_COLS 3
#define N_LINES N_TASKS+1
#define EXECUTION_TIME 50

struct task {
    int p;
    int c;
    int d;
};

struct system {
    struct task tasks[N_TASKS];
    char execution_time_table[N_TASKS][EXECUTION_TIME];
    int tasks_queue[N_TASKS];
};

struct system system;


// -------------------------------------------------------------------------------------

bool p_d_equal () {
    for (int i = 0; i < N_LINES; i++){
        if (system.tasks[i].p != system.tasks[i].d)
            return false;
    }
    return true;
}

float system_utilization () {
    float system_utilization = 0;
    for (int i = 0; i < N_TASKS; i++) {
        system_utilization += system.tasks[i].c/system.tasks[i].p;
    }
}

bool scalability_test () {
    float su = system_utilization();
    if (p_d_equal()) {

    }
}

void print_system_matrix (void) {
    printf("--------\n");
    printf("\tP\tC\tD\n");
    for (int j = 0; j < N_LINES; j++) {
        printf("T%d\t%d\t%d\t%d\n", j+1, system.tasks[j].p, system.tasks[j].c, system.tasks[j].d);
    }
    printf("---------\n\n");
}

void rate_monotonic (void) {
    printf("Rate Monotonic\n");

    int max_value = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max_value){
            max_value = arr[i];
        }
    }
    return max_value;
    

    for (int t = 0; t < EXECUTION_TIME; t++){
        for (int i = 0; i < N_TASKS; i++){

        }
    }
}

void deadline_monotonic (void) {
    printf("Deadline Monotonic\n");
}

void earliest_deadline_first (void) {
    printf("->Earliest Deadline First<-\n");
    printf("------. Escala de Tempo .------\n");
    
    for (int t = 0; t < EXECUTION_TIME; t++) {
        for (int i = 0; i < N_TASKS; i++) {
            
            //system.execution_time_table[i][t] = "O";
        }
    }
}

int read_file (char system_file[]) {    
    FILE *file_ptr = fopen(system_file, "r");
    if (file_ptr == NULL) {
        printf("no such file.\n");
        return 0;
    }
    
    /* 
    Assuming that system.txt has content in below format:
        P       C       D
        4       1       4
        5       2       5
        20      4       20
    */

    for (int i = 0; i < N_LINES; i++){
        fscanf(file_ptr, "%d %d %d ", &system.tasks[i].p, &system.tasks[i].c, &system.tasks[i].d);
    }

    /*
    char save[N_COLS];
    for (int i = 0; fgets(save, N_COLS, file_ptr) != NULL; i++){
        for (int j = 0; j < N_COLS; j++){
            system.tasks[i].p = save[0];
            system.tasks[i].c = save[1];
            system.tasks[i].d = save[2];
        }
    }*/
    return 0;
}

// -------------------------------------------------------------------------------------

int main(void) {

    read_file("./sistemas/sistema1.txt");
    printf("%d\n",system.tasks[2].p);
    
    print_system_matrix();

    char menu_option[4] = {'0','0','0','0'};
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
            rate_monotonic();
        } else
        if (!strcmp(menu_option, "DM")) {
            deadline_monotonic();
        } else
        if (!strcmp(menu_option, "EDF")){
            earliest_deadline_first();
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