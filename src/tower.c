#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tower.h"
#include "graphics.h"
#include "player.h"
#include "map.h"

bool debug;
extern int camera_x;
extern int camera_y;

void main_game_loop(game_t *game)
{
	SDL_Event event;
	int fps;
	int ticks;
	player_t *player; 
	map_t *map;

	player = initialize_player("res/sprites/cursor.png", game->renderer, 
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
	map = initialize_map(game->renderer, "res/sprites/tile.png");

	SDL_SetRelativeMouseMode(true);

	while(game->running){
		while(SDL_WaitEventTimeout(&event, 10))
			handle_input(event, game, player, map);
		SDL_WarpMouseInWindow(game->window, camera_x, camera_y);
		SDL_RenderClear(game->renderer);
		draw_map(map);
		update_player(map, player);
		SDL_RenderPresent(game->renderer);
		ticks = SDL_GetTicks();
		fps = (1000 / 60) - ticks;
		if(ticks < (1000 / 60))
			SDL_Delay(fps);
	}
}

game_t *initialize_game(void)
{
	game_t *game = malloc(sizeof(game_t));
	SDL_Init(SDL_INIT_EVERYTHING);
	game->running = 1;
	game->window = SDL_CreateWindow("Tower", SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	game->renderer = SDL_CreateRenderer(game->window, -1,
			SDL_RENDERER_ACCELERATED);

	if(game->renderer == NULL || game->window == NULL){
		report_error();
		game->running = 0;
		return NULL;
	}
	fprintf(stdout, "Intialized game object\n");
	fprintf(stdout, "\tResolution: %dx%d\n", WIN_WIDTH, WIN_HEIGHT);
	return game;
}

void cleanup(game_t *game)
{
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	IMG_Quit();
	SDL_Quit();
	free(game);
	exit(0);
}

int main(int argc, char **argv)
{
	game_t *game;

	if(argc > 1){
		if(strncmp(argv[1], "debug", strlen(argv[1]) + 1) == 0){
			debug = 1;
			fprintf(stderr, "Running in debug mode\n");
		}
		else
			fprintf(stdout, "Unknown argument,\n");
	}
	else
		fprintf(stdout, "No arguments provided\n");

	game = initialize_game();
	initialize_graphics();
	main_game_loop(game);
	cleanup(game);
	return 0;
}
