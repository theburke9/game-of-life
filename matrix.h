#ifndef GOL_MATRIX_H
#define GOL_MATRIX_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t* data;  // data
    int nrows;      // number of rows
    int ncols;      // number of cols
    size_t size;    // size in bytes of the matrix
} matrix_u8_t;

matrix_u8_t *matrix_create(int nrows, int ncols);
void matrix_destroy(matrix_u8_t *matrix);

uint8_t matrix_get(matrix_u8_t *matrix, int i, int j);
void matrix_set(matrix_u8_t *matrix, int i, int j, uint8_t value);
void matrix_fill(matrix_u8_t *matrix, uint8_t value);

#endif // GOL_MATRIX_H
