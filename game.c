#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOX_W   40
#define BOX_H   40

static bool check_game_ptr(game_t *game);
static int count_neighbors(matrix_u8_t *matrix, int i, int j);

/* CREATION AND DESTRUCTION */

game_t *game_create(int window_width, int window_height) {
    if (window_width <= 0 || window_height <= 0) return NULL;

    int nrows = window_width / BOX_W;
    int ncols = window_height / BOX_H;

    matrix_u8_t *matrix0 = matrix_create(nrows, ncols);
    if (matrix0 == NULL) return NULL;

    matrix_u8_t *matrix1 = matrix_create(nrows, ncols);
    if (matrix1 == NULL) {
        matrix_destroy(matrix0);
        return NULL;
    }

    game_t *game = calloc(1, sizeof(game_t));
    if (game == NULL) {
        matrix_destroy(matrix0);
        matrix_destroy(matrix1);
        return NULL;
    }

    game->grids[0] = matrix0;
    game->grids[1] = matrix1;
    game->current = 0;

    return game;
}

void game_destroy(game_t *game) {
    if (game) free(game);
}

/* STEP AND RENDERING */

void game_step(game_t *game) {
    if (!check_game_ptr(game)) return;

    matrix_u8_t *current = game->grids[game->current];
    matrix_u8_t *next = game->grids[1 - game->current];

    for (int i = 0; i < current->nrows; ++i) {
        for (int j = 0; j < current->ncols; ++j) {
            int n_neighbors = count_neighbors(current, i, j);
            int cell = matrix_get(current, i, j) != 0 ? 1 : 0;
            matrix_set(next, i, j, ((n_neighbors == 3) || (cell == 1 && n_neighbors == 2)) != 0);
        }
    }

    game->current = 1 - game->current;
}

void game_render(game_t *game, SDL_Renderer *renderer) {
    if (!check_game_ptr(game)) return;

    matrix_u8_t *matrix = game->grids[game->current];  

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < matrix->nrows; ++i) {
        for (int j = 0; j < matrix->ncols; ++j) {
            int cell = matrix_get(matrix, i, j) != 0;
            
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

/* STATIC FUNCTIONS */

static bool check_game_ptr(game_t *game) {
    return (game != NULL && game->grids != NULL && game->grids[0] != NULL && game->grids[1] != NULL);
}

static int count_neighbors(matrix_u8_t *matrix, int i, int j) {
    int n = 0;

    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int r = (i + di + matrix->nrows) % matrix->nrows; 
            int c = (j + dj + matrix->ncols) % matrix->ncols;
            n += matrix_get(matrix, r, c) != 0; 
        }
    }

    return n;
}