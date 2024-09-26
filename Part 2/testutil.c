#include <stdio.h>
#include "util.h"

int main() {

    int rows = 3;
    int columns = 4;

    // Call allocateArray to allocate a 2D array
    double *array = (double *)allocateArray(rows, columns);

    // Check if allocation was successful
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Print the array contents (initially all zero)
    printf("Array contents after allocation:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%f ", array[i * columns + j]); // Access 2D array in a flat 1D array
        }
        printf("\n");
    }

    printf("Array contents after allocation:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array[i * columns + j] = i + j; // Access 2D array in a flat 1D array
        }
        printf("\n");
    }

    // Print the array contents
    printf("Array contents after allocation:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%f ", array[i * columns + j]); // Access 2D array in a flat 1D array
        }
        printf("\n");
    }

    // Free the allocated memory
    //free(array);

    return 0;
}