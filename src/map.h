#ifndef MAP_H
#define MAP_H

#include "graphics.h"
#include "cursor.h"

#define MAP_WIDTH 100 
#define MAP_HEIGHT 100

#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

#define TILE_NO_PASS 	false	
#define TILE_PASS 	true	

#define CALC_SCR_ISO_X(x, y) ((y * TILE_WIDTH_HALF) + (x * TILE_WIDTH_HALF)) 
#define CALC_SCR_ISO_Y(x, y) ((x * TILE_HEIGHT_HALF) - (y * TILE_HEIGHT_HALF))

#define CAMERA_OFF_X(game) (game->camera->rect.x)
#define CAMERA_OFF_Y(game) (game->camera->rect.y)

#define IS_ONSCREEN(rect) (rect.x >= -TILE_WIDTH && rect.x <= WIN_WIDTH && \
		rect.y >= -TILE_HEIGHT && rect.y <= WIN_HEIGHT)

typedef struct map_tile_t{
	SDL_Rect rect;
	int sprite;
	bool passable;
	bool onscreen;
}map_tile_t;

typedef struct map_t{
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	SDL_Rect tileset[NUM_TILES];
	map_tile_t *tiles[MAP_WIDTH][MAP_HEIGHT];
}map_t;

map_tile_t *initialize_tile(bool pass, int sprite, int x, int y);
map_t *initialize_map(game_t *game, const char *texture_filename);
map_tile_t *screen_to_grid(game_t *game, int x, int y);
void destroy_tile(map_tile_t *tile);
void destroy_map(map_t *map);
void draw_map(game_t *game);

#endif
