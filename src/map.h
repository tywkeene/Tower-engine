#ifndef MAP_H
#define MAP_H

#include "graphics.h"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

#define TILE_WIDTH_HALF (TILE_WIDTH / 2)
#define TILE_HEIGHT_HALF (TILE_HEIGHT / 2)

typedef struct map_tile_t{
	SDL_Rect rect;
	int sprite;
	bool passable;
}map_tile_t;

typedef struct map_t{
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	SDL_Rect tileset[NUM_TILES];
	map_tile_t *tiles[MAP_WIDTH][MAP_HEIGHT];
}map_t;

map_tile_t *initialize_tile(bool collide, int sprite, int x, int y);
map_tile_t *_2d_to_iso(map_t *map, int x, int y);
map_tile_t *screen_to_iso(map_t *map, int x, int y);
map_tile_t *pixel_to_tile(map_t *map, int x, int y);
void tile_to_pixel(int x, int y, int result[]);
map_t *initialize_map(SDL_Renderer *renderer, const char *texture_filename);
void draw_map(map_t *);

#endif
