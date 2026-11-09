#include "game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>

#define WINDOW_TITLE 	"Game of life"
#define WINDOW_WIDTH 	640
#define WINDOW_HEIGHT 	480

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "ERR: unable to init SDL\n");
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "ERR: unable to create window\n");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
       fprintf(stderr, "ERR: unable to create renderer: %s\n", SDL_GetError());
       return 1;
    }
            
    game_t *game = game_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    matrix_set(game->b0, 11, 10, 1);
    matrix_set(game->b0, 12, 11, 1);
    matrix_set(game->b0, 10, 12, 1);
    matrix_set(game->b0, 11, 12, 1);
    matrix_set(game->b0, 12, 12, 1);
	
	bool isRunning = true;
    while (isRunning) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game_step(game);
        game_render(game, renderer);

        SDL_RenderPresent(renderer);
 
		SDL_Delay(100);
	}

    game_destroy(game);

    SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
