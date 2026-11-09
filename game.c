#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOX_W   20
#define BOX_H   20

static int game_count_neighbors(matrix_u8_t *buffer, int i, int j);

game_t *game_create(int window_width, int window_height) {
    if (window_width <= 0 || window_height <= 0) return NULL;

    int nrows = window_width / BOX_W;
    int ncols = window_height / BOX_H;

    matrix_u8_t *buffer0 = matrix_create(nrows, ncols);
    if (buffer0 == NULL) return NULL;

    matrix_u8_t *buffer1 = matrix_create(nrows, ncols);
    if (buffer1 == NULL) {
        matrix_destroy(buffer0);
        return NULL;
    }

    game_t *game = calloc(1, sizeof(game_t));
    if (game == NULL) {
        matrix_destroy(buffer0);
        matrix_destroy(buffer1);
        return NULL;
    }

    game->b0 = buffer0;
    game->b1 = buffer1;
    game->watch_b0 = true;

    return game;
}

void game_destroy(game_t *game) {
    if (game) free(game);
}

void game_step(game_t *game) {
    matrix_u8_t *buffer_to_write = game->watch_b0 ? game->b1 : game->b0;
    matrix_u8_t *buffer_to_watch = game->watch_b0 ? game->b0 : game->b1;  

    // compute
    for (int i = 0; i < buffer_to_watch->nrows; ++i) {
        for (int j = 0; j < buffer_to_watch->ncols; ++j) {
            int n_neighbors = game_count_neighbors(buffer_to_watch, i, j);
            int cell = matrix_get(buffer_to_watch, i, j) != 0 ? 1 : 0;
            matrix_set(buffer_to_write, i, j, ((n_neighbors == 3) || (cell == 1 && n_neighbors == 2)) != 0);
        }
    }

    game->watch_b0 = !game->watch_b0;
}

void game_render(game_t *game, SDL_Renderer *renderer) {
    matrix_u8_t *buffer = game->watch_b0 ? game->b0 : game->b1;  

    // display
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < buffer->nrows; ++i) {
        for (int j = 0; j < buffer->ncols; ++j) {
            int cell = matrix_get(buffer, i, j) != 0;
            
            if (cell) {
                SDL_FRect rect = { 
                    .x = (float)i * BOX_W, 
                    .y = (float)j * BOX_H, 
                    .w = (float)BOX_W, 
                    .h = (float)BOX_H 
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}


static int game_count_neighbors(matrix_u8_t *buffer, int i, int j) {
    int n = 0;

    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int r = (i + di + buffer->nrows) % buffer->nrows; 
            int c = (j + dj + buffer->ncols) % buffer->ncols;
            n += matrix_get(buffer, r, c) != 0; 
        }
    }

    return n;
}