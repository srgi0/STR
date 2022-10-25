#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "essential.h"

// ------------------------------------------------------------------------------------

#define SYSTEM_FOLDER_PATH  "./sistemas/"

#define N_TASKS 3
#define N_COLS 3
#define N_LINES N_TASKS+1
#define MAX_EXECUTION_TIME 500

struct tasks {
    char name[N_TASKS][10];

    int p[N_TASKS];
    int c[N_TASKS];
    int d[N_TASKS];
};

struct system {
    struct tasks tasks;
    
    int queue_idx_identifier[N_TASKS];

    int total_execution_time;
    char execution_time_table[N_TASKS][MAX_EXECUTION_TIME];

    float utilization;
} System;


// -------------------------------------------------------------------------------------

float system_utilization () {
    System.utilization = 0;
    for (int i = 0; i < N_TASKS; i++) {
        System.utilization += System.tasks.c[i]/System.tasks.p[i];
    }
}

bool scalability_test () {
    float su = system_utilization();
    if (1) {

    }
}

void print_system_matrix (void) {
    printf("--------------------------\n");
    printf("\tP\tC\tD\n");
    for (int j = 0; j < N_TASKS; j++) {
        printf("%s\t%d\t%d\t%d\n", System.tasks.name[j], System.tasks.p[j], System.tasks.c[j], System.tasks.d[j]);
    }
    printf("--------------------------\n\n");
}

void print_system_execution_time_table () {
    printf("Printing Execution Time Table...\n");
    for (int i = 0; i < N_TASKS; i++){
        printf("%s [", System.tasks.name[i]);
        for (int t = 0; t < System.total_execution_time; t++){
            printf("|%c|", System.execution_time_table[i][t]);
        }
        printf("]\n");
    }

    printf(" t (");
    for (int i = 0; i < System.total_execution_time; i++) {
        printf("%02d ", i+1);
    }
    printf(")\n");
}

void rate_monotonic (void) {
    printf("Rate Monotonic (fixed priority)\n");

    array_copy(array_get_idx_sort(System.tasks.p, N_TASKS), System.queue_idx_identifier, N_TASKS);

    /*
    System.execution_time_table[0][0] = 'O';
    System.execution_time_table[1][0] = '-';
    System.execution_time_table[2][0] = '-';
    */

    int idx;
    for (int t=0 ; t<System.total_execution_time ; t++) {
        idx = 0;
        for (int i=0 ; i<N_TASKS; i++) {
            if (i == System.queue_idx_identifier[idx]) {
                idx++;
                for (int c=0 ; c<System.tasks.c[i] ; c++){
                    System.execution_time_table[i][t] = 'O';
                    t++;
                }
            }
        }
        
    }
    

}

void deadline_monotonic (void) {
    printf("->Deadline Monotonic<-\n");
}

void earliest_deadline_first (void) {
    printf("->Earliest Deadline First<-\n");
    printf("------. Escala de Tempo .------\n");
    
    
}


int read_file (char system_file_path[]) {    
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
    for (int i = 0; i < N_LINES;) {
        line++;
        if (!fgets(buf, sizeof buf, file_ptr)) {
            fprintf(stderr, "%s:%d: missing records\n",
                    system_file_path, line);
            break;
        }
        if (sscanf(buf, "%d%d%d", &System.tasks.p[i],
                   &System.tasks.c[i], &System.tasks.d[i]) == 3) {
            sprintf(System.tasks.name[i], "T%d", i);
            i++;
        } else {
            fprintf(stderr, "%s:%d: invalid format: %s", 
                    system_file_path, line, buf);
        } 
    }
    fclose(file_ptr);
    //...
    return 0;

}

void system_init(char system_file_name[]) {
    char system_file_path[50];
    sprintf(system_file_path, "%s%s", SYSTEM_FOLDER_PATH, system_file_name);
    read_file(system_file_path);

    System.total_execution_time = lcm(System.tasks.p, N_TASKS);
    

    print_system_matrix();

    
    // Initializing queue in order [T1, T2, T3, T4, ...]
    for (int i = 0; i < N_TASKS; i++) {
        System.queue_idx_identifier[i] = i;
    }

    // Initializing Execution Time Table filled with '-'
    for (int i=0; i<N_TASKS; i++) {
        for (int t=0; t<System.total_execution_time; t++) {
            System.execution_time_table[i][t] = '-';
        }
    }
    print_system_execution_time_table();
}

// -------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    system_init(argv[1]);


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
            print_system_execution_time_table();
        } else
        if (!strcmp(menu_option, "DM")) {
            deadline_monotonic();
            print_system_execution_time_table();
        } else
        if (!strcmp(menu_option, "EDF")){
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