#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

// int main() {

// 	// Create a list to test our functions with
// 	List* l = (List*) malloc(sizeof(List));
// 	listInit(l, sizeof(int));

// 	// Using this list, let's add a couple ints to make sure we can
// 	int size = 25;
// 	for (int i = 0; i < size; i++) {
// 		listAddEnd(l, &i);
// 	}

// 	// Print the values
// 	for (int i = 0; i < size; i++) {
// 		printf("%d, ", *(int*)listGet(l, i));
// 	}

// 	// Free l and data
// 	free(l -> data);
// 	free(l);
// }

int listInit(List* l, int max_elmt_size) {
	// Make sure l exists
	if (l == NULL) return -1; 

	// Set values, including default max_size 10
	l -> max_size = 10;
	l -> max_element_size = max_elmt_size;
	l -> size = 0;

	// Allocate memory for data
	l -> data = malloc(l -> max_size * l -> max_element_size);

	// Check for memory allocation failure
	if (l -> data == NULL) return -1;

	// Success
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