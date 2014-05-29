#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

#define TILE_WIDTH_HALF (TILE_WIDTH / 2)
#define TILE_HEIGHT_HALF (TILE_HEIGHT / 2)

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

#define TILE_SHEET_ROWS 12
#define TILE_SHEET_WIDTH 256
#define TILE_SHEET_HEIGHT 735

#define NUM_TILES (TILE_SHEET_WIDTH / TILE_WIDTH * TILE_SHEET_ROWS)
#define GFX_INIT_FLAGS (IMG_INIT_PNG | IMG_INIT_JPG)

#define MAP_TEXTURE_FILE "res/sprites/map.png"
#define CURSOR_TEXTURE_FILE "res/sprites/cursor.png"

SDL_Texture *initialize_texture(game_t *game, SDL_Renderer *renderer, const char *filename);
void get_tileset(game_t *game, SDL_Rect set[NUM_TILES]);
int initialize_graphics(void);

#endif
