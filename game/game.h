#ifndef GAME_H
#define GAME_H

#include "core/matrix.h"

typedef struct {
    matrix_u8_t *grids[2];
    int current;
} game_t;

game_t *game_create(int window_width, int window_height);
void game_destroy(game_t *game);

void game_step(game_t *game);
void game_click(game_t *game, int mouse_x, int mouse_y);

#endif // GAME_H
