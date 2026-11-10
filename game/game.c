#include "game/game.h"
#include "game/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool check_game_ptr(game_t *game);
static int count_neighbors(matrix_u8_t *matrix, int i, int j);

/* CREATION AND DESTRUCTION */

game_t *game_create(int window_width, int window_height) {
    if (window_width <= 0 || window_height <= 0) return NULL;

    int nrows = window_width / GAME_CELL_W;
    int ncols = window_height / GAME_CELL_H;

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
    if (game == NULL) return;
    matrix_destroy(game->grids[0]);
    matrix_destroy(game->grids[1]);
    free(game);
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

void game_click(game_t *game, int mouse_x, int mouse_y) {
    if (!check_game_ptr(game)) return;
    int block_x = mouse_x / GAME_CELL_W;
    int block_y = mouse_y / GAME_CELL_H;
    int cell = matrix_get(game->grids[game->current], block_x, block_y) != 0;
    matrix_set(game->grids[game->current], block_x, block_y, !cell);
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