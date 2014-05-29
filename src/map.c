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
	tile->onscreen = false;
	tile->sprite = sprite;

	tile->rect.x = x;
	tile->rect.y = y;

	tile->rect.w = TILE_WIDTH;
	tile->rect.h = TILE_HEIGHT;
	return tile;
}

map_t *initialize_map(game_t *game, const char *texture_filename)
{
	int i, j;
	int x = 0, y = 0;
	map_t *map = malloc(sizeof(map_t));

	map->renderer = game->renderer;
	map->texture = initialize_texture(game, map->renderer, texture_filename);
	get_tileset(game, map->tileset);

	for(i = MAP_WIDTH-1; i >= 0; i--){
		for(j = MAP_HEIGHT-1; j >= 0; j--){
			map->tiles[i][j] = initialize_tile(TILE_PASS, 0, x, y);

			x = CALC_SCR_ISO_X(i, j);
			y = CALC_SCR_ISO_Y(i, j);
		}
	}

	fprintf(stdout, "Initialized map with dimensions (in tiles): %dx%d\n", 
			MAP_WIDTH, MAP_HEIGHT);
	fprintf(stdout, "\tMap Area: %d (tiles)\n", MAP_SIZE);
	return map;
}

map_tile_t *screen_to_grid(game_t *game, int x, int y)
{
	int mapx, mapy;

	x += CAMERA_OFF_X(game);
	y += CAMERA_OFF_Y(game);

	x /= TILE_WIDTH_HALF;
	y /= TILE_HEIGHT_HALF;

	mapx = (x + y) / 2;
	mapy = (x - y) / 2;

	return game->map->tiles[mapx][mapy - 1];
}

void destroy_tile(map_tile_t *tile)
{
	free(tile);
	return;
}

void destroy_map(map_t *map)
{
	int i, j;

	for(i = 0; i < MAP_WIDTH; i++)
		for(j = 0; j < MAP_HEIGHT; j++)
			destroy_tile(map->tiles[i][j]);
	free(map);
	return;
}

void draw_map(game_t *game)
{
	map_tile_t *tile;
	SDL_Rect rect;
	int i, j;

	for(i = MAP_WIDTH - 1; i >= 0; i--){
		for(j = MAP_WIDTH - 1; j >= 0; j--){
			tile = game->map->tiles[i][j];
			rect = tile->rect;

			rect.x -= CAMERA_OFF_X(game);
			rect.y -= CAMERA_OFF_Y(game);

			tile->onscreen = (IS_ONSCREEN(rect)) ? 1 : 0;
			if(tile->onscreen){
				if(SDL_RenderCopy(game->map->renderer, game->map->texture,
							&game->map->tileset[tile->sprite], &rect) != 0){
					report_error();
					game->running = 0;
				}
			}
		}
	}
	return;
}
