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
#include "map.h"

map_tile_t *initialize_tile(bool pass, int sprite, int x, int y)
{
	map_tile_t *tile = malloc(sizeof(map_tile_t));

	tile->passable = pass;
	tile->sprite = sprite;

	tile->rect.x = x;
	tile->rect.y = y;

	tile->rect.w = TILE_WIDTH;
	tile->rect.h = TILE_HEIGHT;
	return tile;
}

map_tile_t *_2d_to_iso(map_t *map, int x, int y)
{
	return map->tiles[(y * TILE_WIDTH / 2 + x * TILE_WIDTH / 2)]
		[(x * TILE_HEIGHT / 2 - y * TILE_HEIGHT / 2)];
}

map_tile_t *pixel_to_tile(map_t *map, int x, int y)
{
	return map->tiles[x / TILE_WIDTH][y / TILE_HEIGHT];
}

map_tile_t *screen_to_iso(map_t *map, int x, int y)
{
	return map->tiles[y * TILE_WIDTH_HALF + x * TILE_WIDTH_HALF]
		[x * TILE_HEIGHT_HALF - y * TILE_HEIGHT_HALF];
}

map_t *initialize_map(game_t *game, const char *texture_filename)
{
	int i, j;
	int x = TILE_WIDTH, y = TILE_HEIGHT;
	map_t *map = malloc(sizeof(map_t));

	map->renderer = game->renderer;
	map->texture = initialize_texture(map->renderer, texture_filename);
	get_tileset(map->tileset);

	for(i = 0; i < MAP_WIDTH; i++)
		for(j = 0; j < MAP_HEIGHT; j++)
			map->tiles[i][j] = malloc(sizeof(map_tile_t));

	for(i = MAP_WIDTH - 1; i >= 0; i--){
		for(j = MAP_HEIGHT - 1; j >= 0; j--){
			map->tiles[i][j] = initialize_tile(1, 0, x, y);

			x = ((j * TILE_WIDTH_HALF) + (i * TILE_WIDTH_HALF) / 2);
			y = ((i * TILE_WIDTH_HALF) - (j * TILE_HEIGHT_HALF) / 2);
		}
	}

	fprintf(stdout, "Initialized map with dimensions (in tiles): %dx%d\n", 
			MAP_WIDTH, MAP_HEIGHT);
	fprintf(stdout, "\t%d total tiles\n", (MAP_WIDTH * MAP_HEIGHT));

	return map;
}

void draw_map(game_t *game)
{
	SDL_Rect *rect;
	int i, j;
	int sprite;

	for(i = MAP_WIDTH - 1; i >= 0; i--){
		for(j = MAP_WIDTH - 1; j >= 0; j--){

			rect = &game->map->tiles[i][j]->rect;

			/*
			rect.x = j * (TILE_WIDTH / 2) + i * (TILE_WIDTH / 2) -
				game->camera->rect.x;
			rect.y = i * (TILE_HEIGHT / 2) - j * (TILE_HEIGHT / 2) -
				game->camera->rect.y;
				*/

			sprite = game->map->tiles[i][j]->sprite;

			if(rect->x <= 10 || rect->x <= WIN_WIDTH ||
					rect->y <= 10 || rect->y <= WIN_HEIGHT)
				if(SDL_RenderCopy(game->map->renderer, game->map->texture,
							&game->map->tileset[sprite], rect) != 0){
					report_error();
					game->running = 0;
				}
		}
	}
}
