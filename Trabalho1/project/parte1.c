#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#include "essential.h"
void swap (int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int max (int arr[], int len){
    int max_value = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max_value){
            max_value = arr[i];
        }
    }
    return max_value;
}

void array_print (int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void array_sort_by_idx (int arr[], int idx[], int n) {
    int temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = arr[idx[i]];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

bool array_copy (int arr1[], int arr2[], int n) {
    for (int i = 0; i < n ; i++) {
        arr2[i] = arr1[i];
    }
}

bool array_equality (int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// returns a pointer (that is like an array)
int* array_get_idx_sort (int arr[], int n) {
    int* idx;
    idx = malloc (sizeof (int) * n);

    for (int i = 0; i < n; i++) {
        idx[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[idx[i]] > arr[idx[j]]){
                swap (&idx[i], &idx[j]);
            }
        }
    }

    return idx;
}


// ------------------------------------------------------------------------------------

#define N_TASKS 3
#define N_COLS 3
#define N_LINES N_TASKS+1
#define EXECUTION_TIME 50

struct tasks {
    int p[N_TASKS];
    int c[N_TASKS];
    int d[N_TASKS];
};

struct system {
    struct tasks tasks;
    
    int queue[N_TASKS];

    char execution_time_table[N_TASKS][EXECUTION_TIME];

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
    printf("--------\n");
    printf("\tP\tC\tD\n");
    for (int j = 0; j < N_TASKS; j++) {
        printf("T%d\t%d\t%d\t%d\n", j+1, System.tasks.p[j], System.tasks.c[j], System.tasks.d[j]);
    }
    printf("---------\n\n");
}

void print_system_execution_time_table () {
    printf("Printing Execution Time Table...\n");
    for (int i = 0; i < N_TASKS; i++){
        printf("T%d [", i+1);
        for (int t = 0; t < EXECUTION_TIME; t++){
            printf("|%c|", System.execution_time_table[i][t]);
        }
        printf("]\n");
    }

    printf(" t (");
    for (int i = 0; i < EXECUTION_TIME; i++) {
        printf("%02d ", i+1);
    }
    printf(")\n");
}

void rate_monotonic (void) {
    printf("Rate Monotonic (fixed priority)\n");

    array_copy(array_get_idx_sort(System.tasks.p, N_TASKS), System.queue, N_TASKS);

    for (int t = 0; t < EXECUTION_TIME; t++){
        for (int i = 0; i < N_TASKS; i++){
            
            for (int c = 0; c < System.tasks.c[i]; c++) {

            }
            System.execution_time_table[i][t] = '-';
        }
    }
}

void deadline_monotonic (void) {
    printf("->Deadline Monotonic<-\n");
}

void earliest_deadline_first (void) {
    printf("->Earliest Deadline First<-\n");
    printf("------. Escala de Tempo .------\n");
    
    for (int t = 0; t < EXECUTION_TIME; t++) {
        for (int i = 0; i < N_TASKS; i++) {
            
            //System.execution_time_table[i][t] = "O";
        }
    }
}

void print_time_scale (void) {
    
}

int read_file (char system_file[]) {    
    /* 
    Assuming that System.txt has content in below format:
        P       C       D
        4       1       4
        5       2       5
        20      4       20
    */
    char buf[256];
    FILE *file_ptr = fopen(system_file, "r");
    if (file_ptr == NULL)
        fprintf(stderr, "cannot open %s\n", system_file);

    int line = 0;
    // skip the header line
    fgets(buf, sizeof buf, file_ptr);
    line++;
    // parse the file contents
    for (int i = 0; i < N_LINES;) {
        line++;
        if (!fgets(buf, sizeof buf, file_ptr)) {
            fprintf(stderr, "%s:%d: missing records\n",
                    system_file, line);
            break;
        }
        if (sscanf(buf, "%d%d%d", &System.tasks.p[i],
                   &System.tasks.c[i], &System.tasks.d[i]) == 3) {
            i++;
        } else {
            fprintf(stderr, "%s:%d: invalid format: %s", 
                    system_file, line, buf);
        } 
    }
    fclose(file_ptr);
    //...
    return 0;

}

void init(char system_file[]) {
    read_file(system_file);
    
    print_system_matrix();
    
    // Initializing queue in order [T1, T2, T3, T4, ...]
    for (int i = 0; i < N_TASKS; i++) {
        System.queue[i] = i;
    }
}

// -------------------------------------------------------------------------------------

int main(void) {

    init("./sistemas/sistema1.txt");


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

        if (strcmp(menu_option, "exit")) {
            if (!strcmp(menu_option, "RM")) {
            rate_monotonic();
            } else
            if (!strcmp(menu_option, "DM")) {
                deadline_monotonic();
            } else
            if (!strcmp(menu_option, "EDF")){
                earliest_deadline_first();
            }

            print_system_execution_time_table();

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