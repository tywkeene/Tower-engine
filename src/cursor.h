#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "map.h"
#include "graphics.h"

#define CURSOR_WIDTH TILE_WIDTH
#define CURSOR_HEIGHT TILE_HEIGHT

typedef struct camera_t{
	SDL_Rect rect;
	int speed;
}camera_t;

typedef struct cursor_t{
    SDL_Rect rect;
    SDL_Rect last;
    SDL_Texture *texture;
    SDL_Rect tileset[NUM_TILES];
    SDL_Renderer *renderer;
    int cur_sprite;
}cursor_t;

void update_cursor(game_t *game);
camera_t *initialize_camera(int x, int y, int speed);
void do_camera_scroll(game_t *game, int x, int y);
void handle_input(SDL_Event event, game_t *game);
cursor_t *initialize_cursor(const char *filename, SDL_Renderer *renderer, int x, int y);

#endif 
