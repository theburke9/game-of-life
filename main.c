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
	
	bool is_running = true;
    bool is_pause = true;
    while (is_running) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    is_running = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_SPACE) {
                        is_pause = !is_pause;
                    }
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    if (event.button.button == SDL_BUTTON_LEFT && is_pause) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        game_click(game, mouseX, mouseY);
                    }
                    break;
                
                default:
                    break;
            }
		}

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (!is_pause)
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
