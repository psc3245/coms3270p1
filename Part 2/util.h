#ifndef UTIL_H
#define UTIL_H

#define INDEX(row, col, total_cols) (row * total_cols + col)

void *allocateArray(int rows, int cols);

typedef struct pdc_t *PCDTPTR;
typedef struct pcd_t {
	double x, y, z;
	double water_amount;
	PCDTPTR north;
	PCDTPTR south;
	PCDTPTR east;	
	PCDTPTR west;

} pcd_t;

typedef struct {
	int max_size;
	int max_element_size;
	void* data;
	int size;
} List;

int listInit(List* l, int max_elmt_size);
void listAddEnd(List* l, void* elmt);
void *listGet(List* l, int index);


#endif