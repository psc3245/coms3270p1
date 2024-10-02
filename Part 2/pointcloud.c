#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"


void imagePointCloud(List *l, int width, char *filename) {

	// Make sure l exists
	if (l == NULL) exit(1);

	// Total entries / entries per row = height
	int height = l -> size / width;

	// Create the bitmap
	Bitmap *b = bm_create(width, height);

	// Ensure malloc within bm_create worked
	if (b == NULL) exit(1);


	// Now that b is set up, begin performing calculations to setup for our bitmap creation

	// First, we need the max and min
	double max_height = 0.0;
	double min_height = 10000000.0;
	double currHeight;
	
	// Find max and min
	for (int i = 0; i < l -> size; i++) {
		pcd_t *address = l -> data + ( i * l -> max_element_size );
		currHeight = (address) -> z;
		if (currHeight > max_height) max_height = currHeight;
		if (currHeight < min_height) min_height = currHeight;
	}

	// Now max_height and min_height contain the max and min heights respectively
	
	// Find the interval over which the heights could be spread
	double interval = (max_height - min_height);

	// Prepare a value to store the rgb value
	double rgb_val;

	int x = 0;
	int y = 0;

	// Color hex
	unsigned int color = 0x0;

	for (int i = 0; i < l -> size; i++) {
		// First, prepare the rgb value
		pcd_t *address = l -> data + ( i * l -> max_element_size );
		currHeight = (address) -> z;
		rgb_val = (round( ((currHeight - min_height) / interval)  * 256.0 ));

		// Now we need to turn this into a 32 bit integer
		color = (0xFF000000) | ((int) rgb_val << 16) | ((int) rgb_val << 8) | ((int) rgb_val);

		bm_set_color(b, color);

		// Now that the color is calculated, put the pixel

		// For some reason it works with x and y backwards

		// If x is less than width, we don't need to increment row, just put the pixel
		if (x < width) {
			bm_putpixel(b, y, x);
		}
		// If x is equal to width, go down a row and reset x to zero, then put the pixel 
		else if (x >= width) {
			// Increment before putting the point because x will be out of bounds otherwise
			y ++;
			x = 0;
			bm_putpixel(b, y, x);
		}

		// Increment x to move a row over
		x ++;
	}

	// Save the bitmap to the file name and free the memory
	bm_save(b, filename);
	bm_free(b);
}

void readPointCloudData(FILE *stream, int *rasterWidth, List *pc) {
	// Make sure stream exists
	if (!stream) return;

	// Initialize variables
	double x;
	double y;
	double z;

	pcd_t current;

	// Start by grabbing the total columns from the top line
	fscanf(stream, "%d", rasterWidth);
	

	// Use scanf to get values from stream
	while (fscanf(stream, "%lf %lf %lf", &x, &y, &z) == 3) {
		// Assign said values to current point
		current.x = x;
		current.y = y;
		current.z = z;

		// Add the point to the list
		listAddEnd(pc, &current);

	}

}

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





