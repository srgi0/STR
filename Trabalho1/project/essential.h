#ifndef ESSENTIAL_H
#define ESSENTIAL_H

extern void swap (int* xp, int* yp);

extern int max (int arr[], int len);

extern void array_print (int arr[], int n);

extern void array_sort_by_idx (int arr[], int idx[], int n);

extern void array_copy (const int arr1[], int arr2[], int n);

extern bool array_equality (int arr1[], int arr2[], int n);

// returns a pointer (that is like an array)
extern int* array_get_idx_sort (int arr[], int n);

int lcm (const int numbers[], int n);



#endif