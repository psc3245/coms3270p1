#include <stdio.h>
#include "pointcloud.h"

void stat1(FILE* fptr) {

	double runningTotal;
	int counter;

	double currentMinHeight;
	struct Point minHeightLocation;

	double currentMaxHeight;
	struct Point maxHeightLocation;

	double x;
	double y;
	double height;

	if (fptr == NULL) {
		return;
	}

	runningTotal = 0.0;
	counter = 0;
	currentMinHeight = 100000000.0;
	currentMaxHeight = 0.0;

	while (fscanf(fptr, "%lf %lf %lf", &x, &y, &height) == 3) {

		runningTotal += height;

		if (height < currentMinHeight) {
			currentMinHeight = height;
			minHeightLocation.x = x;
			minHeightLocation.y = y;
			minHeightLocation.height = height;

		}

		if (height > currentMaxHeight) {
			currentMaxHeight = height;
			maxHeightLocation.x = x;
			maxHeightLocation.y = y;
			maxHeightLocation.height = height;
		}

		counter ++;
	}

	printf("Maximum Height Coordinates: %lf, %lf, %lf \n", 
		maxHeightLocation.x, maxHeightLocation.y, maxHeightLocation.height);

	printf("Minimum Height Coordinates: %lf, %lf, %lf \n", 
		minHeightLocation.x, minHeightLocation.y, minHeightLocation.height);

	double average = runningTotal / counter;
	// printf("Running Total: %lf, %d entries. \n", runningTotal, counter);

	printf("Average Height: %lf", average);

}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 1;
	}

	FILE *fptr = fopen(argv[1], "r");

	if (fptr == NULL) {
		return 1;
	}

	stat1(fptr);
	
	fclose(fptr);
	
	return 0;
}