#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "essential.h"


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