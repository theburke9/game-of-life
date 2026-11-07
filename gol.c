#include <stdio.h>

#include "matrix.h"

int main(void) {
	matrix_u8_t *matrix = matrix_create(5, 8);
	
	int i = 4;
	int j = 6;
	
	printf("nrows=%d, ncols=%d\n", matrix->nrows, matrix->ncols);

	matrix_set(matrix, i, j, 12);
	printf("row=%d, col=%d, val=%u\n", i, j, matrix_get(matrix, i, j));
	matrix_fill(matrix, 10);
	printf("row=%d, col=%d, val=%u\n", i, j, matrix_get(matrix, i, j));
	matrix_destroy(matrix);
	
	return 0;
}

