#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

int main() {
	// Verify that allocateArray works
	
	//double *a;
	// a = (double*) allocateArray(5, 5);

	// for (int i = 0; i < 5; i ++) {
	// 	for (int j = 0; j < 5; j++) {
	// 		*(a + INDEX(i, j, 5)) = i + j;
	// 	}
	// }
	// for (int i = 0; i < 5; i ++) {
	// 	for (int j = 0; j < 5; j++) {
	// 		printf("%f, ", *(a + INDEX(i, j, 5)));
	// 	}
	// 	printf("\n");
	// }

	// Success, allocate array works


	// Testing list init function
	// List* l;
	// listInit(l, sizeof(int));
	// printf("Max Size: %d, Max Element Size: %d, Data pointer: %p, Size: %d \n",
	// 	l-> max_size, l-> max_element_size, &(l-> data), l-> size);

	// Success, the list gets initialized

	List* l = (List*) malloc(sizeof(List));
	listInit(l, sizeof(int));

	// Using this list, let's add a couple ints to make sure we can
	int size = 25;
	for (int i = 0; i < size; i++) {
		listAddEnd(l, &i);
	}

	// Print the values
	for (int i = 0; i < size; i++) {
		printf("%d, ", *(int*)listGet(l, i));
	}

	

	free(l -> data);
	free(l);
}

int listInit(List* l, int max_elmt_size) {

	if (l == NULL) return -1; // failure

	l -> max_size = 10;
	l -> max_element_size = max_elmt_size;
	l -> size = 0;

	l -> data = malloc(l -> max_size * l -> max_element_size);

	if (l -> data == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

	// success
	return 0;
}

void listAddEnd(List* l, void* elmt) {
	// Make sure l exists
	if (l == NULL) return;

	// Check if we need to increase the size
	if (l-> size >= l-> max_size) {
		// Allocate memory for an array twice as big
		void *new_arr = malloc(l -> max_size * l -> max_element_size * 2);

		// Define offset
		int offset;
		// Copy each element
		for (int i = 0; i < l -> size; i ++) {
			// Calculate the offset per element
			offset = i * l -> max_element_size;
			// Copy each element of the array
			memcpy(new_arr + offset, l-> data + offset, l-> max_element_size);
		}
		
		// Set data to the new array
		l -> data = new_arr;

		// Double the max size
		l -> max_size *= 2;
	}

	// If we don't, just place the element at the end of data
	// Calculate the address using size 
	// because size is one greater than the index of the last item
	void *targetAddr = (l-> data + (l-> max_element_size * (l-> size)));

	// Now copy the data from elmt and place it at the calculated address
	memcpy(targetAddr, elmt, l-> max_element_size);

	// Increment size
	l-> size++;

}

void *listGet(List* l, int index) {

	// Make sure index is within bounds
	if (index >= l -> size) return NULL;

	// Calculate the address of the item at index and return it
	void *targetAddr = l -> data + (index) * l -> max_element_size;
	return targetAddr;
}

void *allocateArray(int rows, int cols) {
	double *arr = (double *) calloc(rows * cols, sizeof(double));

	if (arr == NULL) return NULL;

	return (void*) arr;
}