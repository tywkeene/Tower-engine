#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define TILE_SHEET_WIDTH 256
#define TILE_SHEET_HEIGHT 735

#define NUM_TILES (TILE_SHEET_WIDTH / TILE_WIDTH * 12)
#define GFX_INIT_FLAGS (IMG_INIT_PNG | IMG_INIT_JPG)

SDL_Texture *initialize_texture(SDL_Renderer *renderer, const char *filename);
void get_tileset(SDL_Rect set[NUM_TILES]);
int initialize_graphics(void);

#endif
