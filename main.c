// #include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h>

#include <stdio.h>

#include "game.h"

#define WINDOW_TITLE 	"Game of life"
#define WINDOW_WIDTH 	640
#define WINDOW_HEIGHT 	480

int main(int argc, char *argv[]) {
	// if (!SDL_Init(SDL_INIT_VIDEO)) {
	// 	fprintf(stderr, "ERR: unable to init SDL\n");
	// 	return 1;
	// }

	// SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	// if (window == NULL) {
	// 	fprintf(stderr, "ERR: unable to create window\n");
	// 	return 1;
	// }

	// printf("nrows = %d, ncols = %d\n", WINDOW_WIDTH / BOX_W, WINDOW_HEIGHT / BOX_H);

	// bool isRunning = true;
	// while (isRunning) {
	// 	SDL_Event event;
	// 	while(SDL_PollEvent(&event)) {
	// 		if (event.type == SDL_EVENT_QUIT) {
	// 			isRunning = false;
	// 		}
	// 	}

	// 	SDL_Delay(100);
	// }

	// SDL_DestroyWindow(window);

	// SDL_Quit();

    game_t *game = game_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    matrix_set(game->b0, 11, 10, 1);
    matrix_set(game->b0, 12, 11, 1);
    matrix_set(game->b0, 10, 12, 1);
    matrix_set(game->b0, 11, 12, 1);
    matrix_set(game->b0, 12, 12, 1);

    game_display(game);
    game_step(game);
    game_display(game);
    game_step(game);
    game_display(game);
    game_step(game);
    game_display(game);
    game_step(game);
    game_display(game);

    game_destroy(game);

	return 0;
}
