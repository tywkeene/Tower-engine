#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "map.h"
#include "graphics.h"

#define CURSOR_WIDTH 10
#define CURSOR_HEIGHT 10

typedef struct camera_t{
	SDL_Rect rect;
	int speed;
}camera_t;

typedef struct cursor_t{
    int cur_sprite;
    SDL_Rect rect;
    SDL_Rect last;
    SDL_Rect tileset[NUM_TILES];
    SDL_Texture *texture;
    SDL_Renderer *renderer;
}cursor_t;

void update_cursor(game_t *game);
void destroy_camera(camera_t *camera);
camera_t *initialize_camera(game_t *game, int x, int y, int speed);
void camera_goto(game_t *game, int x, int y);
void do_camera_scroll(game_t *game, int x, int y);
void destroy_cursor(cursor_t *cursor);
void handle_input(SDL_Event event, game_t *game);
cursor_t *initialize_cursor(game_t *game, const char *filename, SDL_Renderer *renderer, int x, int y);

#endif
