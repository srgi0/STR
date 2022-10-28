#ifndef ESSENTIAL_H
#define ESSENTIAL_H


// --------------------------------------------------------------------------

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// --------------------------------------------------------------------------

extern void swap (int* xp, int* yp);

extern int array_max (int arr[], int len);

extern void array_print (int arr[], int n);

extern void array_sort_by_idx (int arr[], int idx[], int n);

extern void array_copy (const int arr1[], int arr2[], int n);

extern bool array_equality (int arr1[], int arr2[], int n);

// returns a pointer (that is like an array)
extern int* array_get_idx_sort (int arr[], int n);

int lcm (const int numbers[], int n);

void array_shift (int arr[], int n, int shift);

#endif