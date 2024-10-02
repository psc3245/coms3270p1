#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

// MAKE FILE: gcc -o testing display.c pointcloud.c util.c bmp.c

int main(int argc, char* argv[]) {

	if (argc < 2) {
		return 1;
	}

	FILE *fptr = fopen(argv[1], "r");

	if (fptr == NULL) {
		return 1;
	}

	int rasterWidth;

	List *l = malloc(sizeof(List));
	if (!l) return 1;

	int test = listInit(l, sizeof(pcd_t));
	if (test) return 1;


	readPointCloudData(fptr, &rasterWidth, l);

	char *filename = "./out.gif";

	imagePointCloud(l, rasterWidth, filename);
	
	fclose(fptr);
	
	return 0;
}