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

extern int camera_x;
extern int camera_y;

map_tile_t *initialize_tile(bool pass, int sprite, int x, int y)
{
	map_tile_t *tile = malloc(sizeof(map_tile_t));
	if(debug)
		tile->passable = 1;
	else
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

map_t *initialize_map(SDL_Renderer *renderer, const char *texture_filename)
{
	int i, j;
	int x = 0, y = 0;
	map_t *map = malloc(sizeof(map_t));
	map->renderer = renderer;
	map->texture = initialize_texture(map->renderer, texture_filename);
	get_tileset(map->tileset);

	for(i = 0; i < MAP_WIDTH; i++){
		for(j = 0; j < MAP_HEIGHT; j++){
			map->tiles[i][j] = malloc(sizeof(map_tile_t));
			map->tiles[i][j] = initialize_tile(1, 0, x, y);
			x += TILE_WIDTH;
			y += TILE_HEIGHT;
		}
	}

	fprintf(stdout, "Initialized map with dimensions (in tiles): %dx%d\n", 
			(MAP_WIDTH), (MAP_HEIGHT));
	fprintf(stdout, "\t%d total tiles\n", 
			(MAP_WIDTH) * (MAP_HEIGHT));

	return map;
}

void draw_map(map_t *map)
{
	SDL_Rect rect;
	int i, j;
	int sprite;
	for(i = MAP_WIDTH - 1; i > 0; i--){
		for(j = MAP_WIDTH - 1; j > 0; j--){

			rect = map->tiles[i][j]->rect;

			rect.x = j * (TILE_WIDTH / 2) + i * (TILE_WIDTH / 2) - camera_x;
			rect.y = i * (TILE_HEIGHT / 2) - j * (TILE_HEIGHT / 2) - camera_y;

			sprite = map->tiles[i][j]->sprite;

			if(rect.x <= 10 || rect.x <= WIN_WIDTH ||
					rect.y <= 10 || rect.y <= WIN_HEIGHT)
				if(SDL_RenderCopy(map->renderer, map->texture,
							&map->tileset[sprite], &rect) != 0)
					report_error();
		}
	}
}
