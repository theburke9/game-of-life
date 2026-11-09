#ifndef GAME_H
#define GAME_H

#include "matrix.h"
#include <SDL3/SDL.h>

typedef struct {
    matrix_u8_t *grids[2];
    int current;
} game_t;

game_t *game_create(int window_width, int window_height);
void game_destroy(game_t *game);

void game_step(game_t *game);
void game_render(game_t *game, SDL_Renderer *renderer);

#endif // GAME_H
