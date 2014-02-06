#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#define WIN_WIDTH 880
#define WIN_HEIGHT 880

#define TILE_SHEET_WIDTH 60
#define TILE_SHEET_HEIGHT 60
#define TILE_SIZE 20

#define NUM_TILES (TILE_SHEET_WIDTH * 3 / TILE_SIZE)
#define GFX_INIT_FLAGS IMG_INIT_PNG | IMG_INIT_JPG

SDL_Texture *initialize_texture(SDL_Renderer *renderer, const char *filename);
void get_tileset(SDL_Rect set[NUM_TILES]);
int initialize_graphics(void);

#endif
