#include "render/render.h"
#include "game/config.h"

void game_render(game_t *game, SDL_Renderer *renderer) {
    matrix_u8_t *matrix = game->grids[game->current];  

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < matrix->nrows; ++i) {
        for (int j = 0; j < matrix->ncols; ++j) {
            int cell = matrix_get(matrix, i, j) != 0;
            
            if (cell) {
                SDL_FRect rect = { 
                    .x = (float)i * GAME_CELL_W, 
                    .y = (float)j * GAME_CELL_H, 
                    .w = (float)GAME_CELL_W, 
                    .h = (float)GAME_CELL_H 
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
