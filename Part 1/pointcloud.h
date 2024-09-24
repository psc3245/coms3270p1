// Header file for pointcloud.c
// pointcloud.c currently only contains one method besides main, so this is pretty short

#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <stdio.h>

// Declarations below
void stat1(FILE* fptr);

typedef struct Point {
	double x;
	double y;
	double height;
} Point ;

#endif