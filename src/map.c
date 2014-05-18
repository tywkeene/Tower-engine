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
	tile->x = x;
	tile->y = y;
	return tile;
}

map_tile_t *pixel_to_tile(map_t *map, int x, int y)
{
	return map->tiles[x / TILE_WIDTH][y / TILE_HEIGHT];
}

map_t *initialize_map(SDL_Renderer *renderer, const char *texture_filename)
{
	int i, j;
	int x, y;
	map_t *map = malloc(sizeof(map_t));
	map->renderer = renderer;
	map->texture = initialize_texture(map->renderer, texture_filename);
	get_tileset(map->tileset);

	for(i = 0, x = 0; i < WIN_WIDTH / TILE_WIDTH&& x < WIN_WIDTH; i++, x += TILE_WIDTH){
		for(j = 0, y = 0; j < WIN_HEIGHT / TILE_HEIGHT&& y < WIN_HEIGHT; j++, y += TILE_HEIGHT){
			map->tiles[i][j] = malloc(sizeof(map_tile_t));
			map->tiles[i][j] = initialize_tile(1, 0, x, y);
		}
	}
	fprintf(stdout, "Initialized map with dimensions (in tiles): %dx%d\n", 
			(WIN_WIDTH / TILE_WIDTH), (WIN_HEIGHT / TILE_HEIGHT));
	fprintf(stdout, "\t%d total tiles\n", 
			(WIN_WIDTH / TILE_WIDTH) + (WIN_HEIGHT / TILE_HEIGHT));

	return map;
}

void draw_map(map_t *map)
{
	SDL_Rect rect;
	int i, j, r;
	int sprite;
	for(i = 0; i < WIN_WIDTH / TILE_WIDTH; i++){
		for(j = 0; j < WIN_HEIGHT / TILE_HEIGHT; j++){
			rect.h = TILE_HEIGHT;
			rect.w = TILE_WIDTH;

			rect.x = j * TILE_WIDTH / 2 + i * TILE_WIDTH / 2 - camera_x;
			rect.y = i * TILE_HEIGHT / 2 - j * TILE_HEIGHT / 2 - camera_y;

			sprite = map->tiles[i][j]->sprite;
			if(SDL_RenderCopy(map->renderer, map->texture,
						&map->tileset[sprite], &rect) != 0)
				report_error();
		}
	}
}
