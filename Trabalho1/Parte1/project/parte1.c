#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "essential.h"

// ------------------------------------------------------------------------------------

#define SYSTEM_FOLDER_PATH  "./sistemas/"

#define MAX_N_TASKS 50
#define MAX_N_LINES MAX_N_TASKS+1
#define MAX_EXECUTION_TIME 500

#define QUEUE_OPENING 0

struct tasks {
    char name[MAX_N_TASKS][10];

    int p[MAX_N_TASKS];
    int c[MAX_N_TASKS];
    int d[MAX_N_TASKS];

    int remaining_c[MAX_N_TASKS];
    int absolute_d[MAX_N_TASKS];
};

struct system {
    struct tasks tasks;
    
    int queue_task_idx_identifier[MAX_N_TASKS];

    int period_time;
    int number_of_periods;
    int total_execution_time;
    int execution_time_table_size_type;
    
    char execution_time_table[MAX_N_TASKS][MAX_EXECUTION_TIME];

    float utilization;
    float deadline_utilization;

    float max_utilization;
} System;

int n_tasks;

// -------------------------------------------------------------------------------------

void calc_system_utilization () {
    for (int i=0 ; i<n_tasks ; i++) {
        System.utilization += (float) System.tasks.c[i] / (float) System.tasks.p[i];

        System.deadline_utilization += (float) System.tasks.c[i] / (float) System.tasks.d[i];
    }
}

void print_system_matrix (void) {
    printf("--------------------------\n");
    printf("\tP\tC\tD\n");
    for (int j = 0; j < n_tasks; j++) {
        printf("%s\t%d\t%d\t%d\n", System.tasks.name[j], System.tasks.p[j], System.tasks.c[j], System.tasks.d[j]);
    }
    printf("--------------------------\n");
}

void set_execution_time_table () {
    for (int i=0; i<n_tasks; i++) {
        for (int t=0; t<System.total_execution_time; t++) {
            System.execution_time_table[i][t] = '-';
        }
    }
}

void print_system_execution_time_table () {
    #define period_color BRED
    #define task_color CYNB
    #define notask_color BYEL

    printf("Printing %d period Execution Time Table...\n", System.number_of_periods);
    for (int i = 0; i < n_tasks; i++){
        printf("%s [", System.tasks.name[i]);
        for (int t = 0; t < System.total_execution_time; t++){
            if (! (t % System.tasks.p[i]))
                printf(period_color "|" CRESET);
            else
                printf("|");

            if (System.execution_time_table[i][t] == 'O')
                printf(task_color " " CRESET);
            else
                printf(notask_color "%c" CRESET, System.execution_time_table[i][t]);
            printf("|");
        }

        if (! (System.total_execution_time % System.tasks.p[i]))
            printf(period_color);
        printf("|" CRESET);
        printf("]\n");
    }

    printf(" t (");
    for (int i = 0; i < System.total_execution_time; i++) {
        printf("%02d ", i+1);
    }
    printf(")\n");
    printf("\n");


    #undef period_color
    #undef task_color
    #undef notask_color
}

void rate_monotonic_criterion (int t) {
    // Ordering the queue in function of tasks period time
    int* queue_aux;
    queue_aux = array_get_idx_sort(System.tasks.p, n_tasks);
    array_copy(queue_aux, System.queue_task_idx_identifier, n_tasks);
}

void deadline_monotonic_criterion (int t) {
    int* queue_aux;
    queue_aux = array_get_idx_sort(System.tasks.d, n_tasks);
    array_copy(queue_aux, System.queue_task_idx_identifier, n_tasks);
}

void earliest_deadline_first_criterion (int t) {
    for (int i=0 ; i<n_tasks ; i++) {
        if (t >= System.tasks.absolute_d[i])
            System.tasks.absolute_d[i] += System.tasks.d[i];
    }

    int* queue_aux;
    queue_aux = array_get_idx_sort(System.tasks.absolute_d, n_tasks);
    array_copy(queue_aux, System.queue_task_idx_identifier, n_tasks);
}

void escalonador (void (*queue_priority_criterion) (int time)) {
    // Initializing tasks remaining runtime (real time c)
    for (int i=0 ; i<n_tasks ; i++) {
        System.tasks.remaining_c[i] = System.tasks.c[i];
    }
    // Initializing tasks absolute deadline (real time d)
    for (int i=0 ; i<n_tasks ; i++) {
        System.tasks.absolute_d[i] = System.tasks.d[i];
    }

    set_execution_time_table();

    int aux;
    for (int t=0; t<System.total_execution_time ; t++) {
        // criterio de prioridade para a fila
        (*queue_priority_criterion)(t);

        // Polling para esperar uma tarefa pedir para entrar na fila (deu
        // o seu periodo).
        for (int i=0 ; i<n_tasks ; i++) {
            if (! (t % System.tasks.p[i])) {
                System.tasks.remaining_c[i] = System.tasks.c[i];
            }
        }
        // Quando acabar a execu????o de uma tarefa, ela vai para o final da fila e a pr??xima
        // tarefa vai para o in??cio (shift)
        for (int i=0 ; i<n_tasks-1 ; i++) {
            if (! System.tasks.remaining_c[System.queue_task_idx_identifier[QUEUE_OPENING]]) {
            array_shift(System.queue_task_idx_identifier, n_tasks, -1);
            }
        }
        
        
        aux = System.queue_task_idx_identifier[QUEUE_OPENING];
        if (System.tasks.remaining_c[aux]) {
            System.execution_time_table[aux][t] = 'O';
            System.tasks.remaining_c[aux]--;
        }
        
    }
}

void escalabilidade_check (void) {
    #define PRIORITY_TYPE       GRN
    #define SCALABILITY_TEST    RED
    
    printf("---------------------------------------------\n");

    printf("System Utilization = %.2f%%\n", System.utilization*100);
    printf(PRIORITY_TYPE "[Fixed priority]\n" CRESET);
    System.max_utilization = (float) n_tasks*(pow(2.0,(1.0/n_tasks)) - 1);
    printf("\tMax utilization = %.2f%%\n", System.max_utilization*100);

    printf(SCALABILITY_TEST);
    if (System.utilization <= System.max_utilization) {
        printf("\t-> O sistema ?? escalon??vel (teste suficiente mas n??o necess??rio)\n");
    }
    else {
        printf("\t-> N??o passou no teste suficiente mas n??o necess??rio\n");
    }
    printf(CRESET);
    

    printf(PRIORITY_TYPE "[Variable priority]\n" CRESET);
    System.max_utilization = 1.0;
    printf("\tMax utilization = %.2f%%\n", System.max_utilization*100);
    if (array_equality(System.tasks.d, System.tasks.p, n_tasks)) {
        printf("\t D=P (Teste Exato)\n");
        printf(SCALABILITY_TEST);
        if (System.utilization <= 1)
            printf("\t\t-> O sistema ?? escalon??vel (permite usar 100%% do processador mantendo os deadlines)\n");
        else
            printf("\t\t-> N??o passou no teste exato\n");

        printf(CRESET);
    }
    else {
        printf("\t D<P (Teste suficiente)\n");
        printf("Deadline Utilization = %.2f%%\n", System.deadline_utilization);
        printf(SCALABILITY_TEST);
        if (System.deadline_utilization <= 1)
            printf("\t\t-> O sistema ?? escalon??vel\n");
        else
            printf("\t\t-> N??o passou no teste suficiente\n");

        printf(CRESET);
    }
    


    printf("---------------------------------------------\n");
}

void rate_monotonic (void) {
    printf(RED ">>>Rate Monotonic (fixed priority)<<<\n" CRESET);
    escalonador(rate_monotonic_criterion);
    
}

void deadline_monotonic (void) {
    printf(RED ">>>Deadline Monotonic<<<\n" CRESET);
    escalonador(deadline_monotonic_criterion);
}

void earliest_deadline_first (void) {
    printf(RED ">>>Earliest Deadline First (variable priority)<<<\n" CRESET);
    escalonador(earliest_deadline_first_criterion);
}



int read_file (char system_file_path[]) {
    int nlines = 0;

    /* 
    Assuming that System.txt has content in below format:
        P       C       D
        4       1       4
        5       2       5
        20      4       20
    */
    char buf[256];
    FILE *file_ptr = fopen(system_file_path, "r");
    if (file_ptr == NULL)
        fprintf(stderr, "cannot open %s\n", system_file_path);

    int line = 0;
    // skip the header line
    fgets(buf, sizeof buf, file_ptr);
    line++;
    // parse the file contents
    for (int i = 0; i < MAX_N_LINES;) {
        line++;
        if (!fgets(buf, sizeof buf, file_ptr)) {
            fprintf(stderr, "%s:%d: missing records\n",
                    system_file_path, line);
            break;
        }
        if (sscanf(buf, "%d%d%d", &System.tasks.p[i],
                   &System.tasks.c[i], &System.tasks.d[i]) == 3) {
            sprintf(System.tasks.name[i], "T%d", i+1);
            i++;
            nlines++;
        } else {
            fprintf(stderr, "%s:%d: invalid format: %s", 
                    system_file_path, line, buf);
        } 
    }
    fclose(file_ptr);
    //...
    return nlines;
}

void system_init(char system_file_name[]) {
    char system_file_path[50];
    sprintf(system_file_path, "%s%s", SYSTEM_FOLDER_PATH, system_file_name);
    n_tasks = read_file(system_file_path);


    System.period_time = lcm(System.tasks.p, n_tasks);
    printf("Execution Time Table size [system period (0) | larger task period (1)]: ");
    scanf("%d", &System.execution_time_table_size_type);
    if (System.execution_time_table_size_type)
        System.total_execution_time = array_max(System.tasks.p, n_tasks);
    else{
        System.number_of_periods = 1;
        System.total_execution_time = System.number_of_periods*System.period_time;
    }
    printf("%d\n", System.period_time);
    
    printf("%s\n", system_file_name);
    print_system_matrix();

    calc_system_utilization();
    
    // Initializing queue in order [T1, T2, T3, T4, ...]
    for (int i = 0; i < n_tasks; i++) {
        System.queue_task_idx_identifier[i] = i;
    }
    
    escalabilidade_check();

    // Initializing Execution Time Table filled with '-'
    set_execution_time_table();
    print_system_execution_time_table();
}

void menu_screen (char menu_option[]) {
    printf("----------------------------------------------\n");
    printf("Escolha o Algoritmo de Escalonamento ou <exit> para sair:\n");
    printf("\t- <RM> (Rate Monotonic)\n");
    //printf("\t- <DM> (Deadline Monotonic)\n");
    printf("\t- <EDF> (Earliest Deadline First)\n");
    printf("\t- <exit> (Sair do programa)\n");
    printf("--> ");
    scanf("%s", menu_option);
    printf("\n");
}

// -------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    system_init(argv[1]);


    char menu_option[4] = {'0','0','0','0'};
    while (strcmp(menu_option, "exit")) {
        /*
        printf("----------------------------------------------\n");
        printf("Number of system periods: ");
        scanf("%d", &System.number_of_periods);
        System.total_execution_time = System.number_of_periods*System.period_time;
        printf("----------------------------------------------\n");
        */

        menu_screen(menu_option);

        if (!strcmp(menu_option, "RM")) {
            system("clear");
            printf("%s\n", argv[1]);
            print_system_matrix();
            escalabilidade_check();

            rate_monotonic();
            print_system_execution_time_table();
        } else
        /*if (!strcmp(menu_option, "DM")) {
            system("clear");
            printf("%s\n", argv[1]);
            print_system_matrix();
            escalabilidade_check();

            deadline_monotonic();
            print_system_execution_time_table();
        } else*/
        if (!strcmp(menu_option, "EDF")){
            system("clear");
            printf("%s\n", argv[1]);
            print_system_matrix();
            escalabilidade_check();

            earliest_deadline_first();
            print_system_execution_time_table();
        } 
        else
        if (!strcmp(menu_option, "exit")){
            printf("Saindo...\n");
        }
        else {
            printf("Opcao invalida\n");
        }

    }

    







return(0);
}