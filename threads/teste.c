#include <stdio.h>

#define NUMBER_OF_STRING 4
#define MAX_STRING_SIZE 40

char arr[NUMBER_OF_STRING][MAX_STRING_SIZE] =
{ "array of c string",
  "is fun to use",
  "make sure to properly",
  "tell the array size"
};


int main(void) {
	for (int i; i<NUMBER_OF_STRING; i++)
		printf("%s\n",arr[i]);



	return 0;
}
