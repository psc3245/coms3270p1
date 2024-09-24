stat: pointcloud.o
	gcc -g pointcloud.o -o stat
pointcloud.o: pointcloud.c pointcloud.h
	gcc -c -g pointcloud.c