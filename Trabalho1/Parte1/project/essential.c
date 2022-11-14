#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "essential.h"


void swap (int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int array_max (int arr[], int len){
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

void array_copy (const int arr1[], int arr2[], int n) {
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
            if (arr[idx[i]] < arr[idx[j]]){
                swap (&idx[i], &idx[j]);
            }
        }
    }

    return idx;
}

void array_scalar_multiply (int arr[], int scalar, int n) {
    for (int i=0 ; i<n; i++) {
        arr[i] *= scalar;
    }
}

void array_divide (int arr[], int div, int n) {
    for (int i=0 ; i<n; i++) {
        if (!(arr[i] % div)) {
            arr[i] /= div;
        }
    }
}

bool array_all_one (int arr[], int n) {
    for (int i=0 ; i<n ; i++) {
        if (arr[i] != 1) {
            return false;
        }
    }
    return true;
}

int lcm (const int numbers[], int n) {
    int numbers_cp[n];
    array_copy(numbers, numbers_cp, n);

    int primo[6] = {2,3,5,7,11,13};

    int lcm = 1;

    for (int aux=0 ; aux < 6; aux++) {
        for (int i=0 ; i<n && !array_all_one(numbers_cp, n) ; i++) {
            if ((numbers_cp[i] % primo[aux] == 0)) {
                lcm *= primo[aux];
                array_divide(numbers_cp, primo[aux], n);
                aux = -1;
            }
        }

    }
    return lcm;
}

void array_shift (int arr[], int n, int shift) {
    if (shift >= 0) {
        for (int s=0; s<shift ; s++) {
            for (int i=(n-1) ; i>0; i--) {
                swap(&arr[i], &arr[i-1]);
            }
        }
    }
    else {
        for (int s=0; s<abs(shift) ; s++) {
            for (int i=0 ; i<n-1; i++) {
                swap(&arr[i], &arr[i+1]);
            }
        }
    }
    
}