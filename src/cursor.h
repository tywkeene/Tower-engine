#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "graphics.h"
#include "map.h"

typedef struct cursor_t{
    SDL_Rect rect;
    SDL_Rect last;
    SDL_Texture *texture;
    SDL_Rect tileset[NUM_TILES];
    SDL_Renderer *renderer;
    int cur_sprite;
}cursor_t;

void initialize_camera(game_t *game, map_t *map);
void update_cursor(map_t *map, cursor_t *cursor);
void handle_input(SDL_Event event, game_t *game, cursor_t *cursor, map_t *map);
cursor_t *initialize_cursor(const char *filename, SDL_Renderer *renderer, int x, int y);

#endif 
