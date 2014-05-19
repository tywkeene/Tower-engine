#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tower.h"
#include "graphics.h"
#include "cursor.h"
#include "map.h"

int camera_y;
int camera_x;

void update_cursor(map_t *map, cursor_t *cursor)
{
	SDL_RenderCopy(cursor->renderer, cursor->texture, 
			&cursor->tileset[cursor->cur_sprite], &cursor->rect);
}

void initialize_camera(game_t *game, map_t *map)
{
	int x, y;

	x = map->tiles[MAP_WIDTH / 2][MAP_HEIGHT / 2]->rect.x;
	y = map->tiles[MAP_WIDTH / 2][MAP_HEIGHT / 2]->rect.y;

	/*
	camera_x = (y * (TILE_WIDTH / 2) + x * (TILE_WIDTH / 2));
	camera_y = (x * (TILE_WIDTH / 2) - y * (TILE_WIDTH / 2));
	*/

	camera_x = x;
	camera_y = y;

	SDL_SetRelativeMouseMode(true);
}

void do_camera_scroll(cursor_t *cursor, int x, int y)
{
	if(x <= 10)
		camera_x -= 4;
	else if(x >= (WIN_WIDTH - 10))
		camera_x += 4;

	if(y <= 10)
		camera_y -= 4;
	else if(y >= (WIN_HEIGHT - 10))
		camera_y += 4;

	cursor->rect.y = y;
	cursor->rect.x = x;
}

void handle_input(SDL_Event event, game_t *game, cursor_t *cursor, map_t *map)
{
	int x, y;

	SDL_GetMouseState(&x, &y);

	switch(event.type){
	case SDL_QUIT:
		game->running = false;
		break;
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_q)
			game->running = false;
	case SDL_MOUSEBUTTONDOWN:
		break;
	case SDL_MOUSEBUTTONUP:
		break;

	case SDL_MOUSEMOTION:
		do_camera_scroll(cursor, x, y);
		break;
	default:
		break;
	}
}

cursor_t *initialize_cursor(const char *filename, SDL_Renderer *renderer, int x, int y)
{
	cursor_t *cursor = malloc(sizeof(cursor_t));
	cursor->rect.h = 32;
	cursor->rect.w = 64;
	fprintf(stdout, "(%d,%d)\n",x, y);
	cursor->rect.x = x;
	cursor->rect.y = y;
	cursor->last = cursor->rect;

	cursor->renderer = renderer;
	cursor->cur_sprite = 0;
	cursor->texture = initialize_texture(cursor->renderer, filename);
	get_tileset(cursor->tileset);
	return cursor;
}

