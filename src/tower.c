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
#include "cursor.h"
#include "graphics.h"
#include "map.h"

#define FPS 60

void cap_frame_rate(void)
{
	static uint32_t last = 0;
	uint32_t curr;

	if((curr = SDL_GetTicks() - last) < 1000.f / FPS)
		SDL_Delay((1000.f / FPS ) - curr);
	last = SDL_GetTicks();
	return;
}

void main_game_loop(game_t *game)
{
	SDL_Event event;

	cap_frame_rate();

	while(game->running){
		while(SDL_PollEvent(&event))
			handle_input(event, game);

		SDL_RenderClear(game->renderer);

		draw_map(game);
		update_cursor(game);

		SDL_RenderPresent(game->renderer);
		cap_frame_rate();
	}
	return;
}

game_t *initialize_game(void)
{
	int cam_starty, cam_startx;
	game_t *game = malloc(sizeof(game_t));

	SDL_Init(SDL_INIT_EVERYTHING);

	game->running = 1;

	game->window = SDL_CreateWindow("Tower engine", SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

	if(game->renderer == NULL || game->window == NULL){
		game->running = 0;
		report_error();
	}

	game->camera = initialize_camera(game, 0, 0, 5);
	game->map = initialize_map(game, MAP_TEXTURE_FILE);

	cam_startx = game->map->tiles[MAP_WIDTH/2][MAP_HEIGHT/2]->rect.x;
	cam_starty = game->map->tiles[MAP_WIDTH/2][MAP_HEIGHT/2]->rect.y;
	camera_goto(game, cam_startx, cam_starty);

	game->cursor = initialize_cursor(game, CURSOR_TEXTURE_FILE, game->renderer,
			cam_startx/2, cam_starty/2);

	SDL_SetRelativeMouseMode(true);

	initialize_graphics();

	fprintf(stdout, "Intialized game object\n");
	fprintf(stdout, "\tResolution: %dx%d\n", WIN_WIDTH, WIN_HEIGHT);
	return game;
}

void sdl_cleanup(game_t *game)
{
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	IMG_Quit();
	SDL_Quit();
	return;
}

void engine_cleanup(game_t *game)
{
	destroy_map(game->map);
	destroy_cursor(game->cursor);
	destroy_camera(game->camera);

	sdl_cleanup(game);
	free(game);
	return;
}

void show_version_info(void)
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	fprintf(stdout, "Compiled against SDL version %d.%d.%d\n",
			compiled.major, compiled.minor, compiled.patch);
	fprintf(stdout, "Linked against SDL version %d.%d.%d\n",
			linked.major, linked.minor, linked.patch);
	return;
}

int main(int argc, char **argv)
{
	game_t *game;

	show_version_info();

	if((game = initialize_game()) == NULL)
		exit(-1);

	if(argc > 1){
		if(strncmp(argv[1], "debug", strlen(argv[1]) + 1) == 0){
			game->debug = 1;
			fprintf(stderr, "Running in debug mode\n");
		}
		else
			fprintf(stdout, "Unknown argument,\n");
	}
	else
		fprintf(stdout, "No arguments provided\n");

	main_game_loop(game);
	engine_cleanup(game);
	return 0;
}
