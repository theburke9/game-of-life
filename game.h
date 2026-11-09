#ifndef GAME_H
#define GAME_H

#include "matrix.h"

typedef struct {
    matrix_u8_t *b0;
    matrix_u8_t *b1;
    bool watch_b0;
} game_t;

game_t *game_create(int window_width, int window_height);
void game_destroy(game_t *game);

void game_step(game_t *game);
void game_display(game_t *game);

#endif // GAME_H
