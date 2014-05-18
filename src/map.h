#ifndef MAP_H
#define MAP_H

#include "graphics.h"

#define MAP_WIDTH (WIN_WIDTH / TILE_SIZE)
#define MAP_HEIGHT (WIN_HEIGHT / TILE_SIZE)
#define MAP_SIZE (MAP_HEIGHT * MAP_WIDTH)

typedef struct map_tile_t{
    int x;
    int y;
    int sprite;
    bool passable;
}map_tile_t;

typedef struct map_t{
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Rect tileset[NUM_TILES];
    map_tile_t *tiles[WIN_WIDTH / TILE_WIDTH] [WIN_HEIGHT / TILE_HEIGHT];
}map_t;

map_tile_t *initialize_tile(bool collide, int sprite, int x, int y);
map_tile_t *pixel_to_tile(map_t *map, int x, int y);
void tile_to_pixel(int x, int y, int result[]);
map_t *initialize_map(SDL_Renderer *renderer, const char *texture_filename);
void draw_map(map_t *);

#endif
