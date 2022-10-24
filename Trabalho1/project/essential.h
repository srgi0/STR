#ifndef ESSENTIAL_H
#define ESSENTIAL_H

void swap (int* xp, int* yp);

int max (int arr[], int len);

void array_print (int arr[], int n);

void array_sort_by_idx (int arr[], int idx[], int n);

bool array_copy (int arr1[], int arr2[], int n);

bool array_equality (int arr1[], int arr2[], int n);

// returns a pointer (that is like an array)
int* array_get_idx_sort (int arr[], int n);



#endif