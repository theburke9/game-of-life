#include "matrix.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool check_matrix_ptr(matrix_u8_t *matrix) {
    return matrix != NULL && matrix->data != NULL;
}

static bool check_matrix_boundaries(matrix_u8_t *matrix, int i, int j) {
    return check_matrix_ptr(matrix) 
        && (i >= 0 && i < matrix->nrows) 
        && (j >= 0 && j < matrix->ncols);
}

static bool compute_data_size(int a, int b, size_t *out) {
    if (out == NULL || a < 0 || b < 0) return false;
    
    size_t r = (size_t)a;
    size_t c = (size_t)b;

    if (c != 0 && r > SIZE_MAX / c) return false;

    *out = r * c;

    return true;
}

matrix_u8_t *matrix_create(int nrows, int ncols) {
    size_t matrix_struct_size = sizeof(matrix_u8_t);
    size_t data_size;
    
    if (!compute_data_size(nrows, ncols, &data_size)) return NULL;
    if (data_size > SIZE_MAX - matrix_struct_size) return NULL;
    
    matrix_u8_t *matrix = calloc(1, matrix_struct_size + data_size);
    if (matrix == NULL) return NULL;

    matrix->data = (uint8_t*)(matrix + 1);
    matrix->nrows = nrows;
    matrix->ncols = ncols;
    matrix->size = data_size;

    return matrix;
}

void matrix_destroy(matrix_u8_t *matrix) {
    if (matrix) free(matrix);
}

uint8_t matrix_get(matrix_u8_t *matrix, int i, int j) {
    if (!check_matrix_boundaries(matrix, i, j)) return 0;
    return matrix->data[j + i * matrix->ncols];
}

void matrix_set(matrix_u8_t *matrix, int i, int j, uint8_t value) {
    if (!check_matrix_boundaries(matrix, i, j)) return;
    matrix->data[j + i * matrix->ncols] = value;
}

void matrix_fill(matrix_u8_t *matrix, uint8_t value) {
    if (!check_matrix_ptr(matrix)) return;
    memset(matrix->data, value, matrix->size);
}
