#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t* data;  // data
    int nrows;      // number of rows
    int ncols;      // number of cols
    size_t size;    // size in bytes of the data buffer
} matrix_u8_t;

matrix_u8_t *matrix_create(int nrows, int ncols);
void matrix_destroy(matrix_u8_t *matrix);

uint8_t matrix_get(const matrix_u8_t *matrix, int i, int j);
void matrix_set(matrix_u8_t *matrix, int i, int j, uint8_t value);
void matrix_fill(matrix_u8_t *matrix, uint8_t value);

#endif // CORE_MATRIX_H
