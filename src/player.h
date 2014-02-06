#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "graphics.h"
#include "map.h"

typedef struct player_t{
    SDL_Rect rect;
    SDL_Rect last;
    SDL_Texture *texture;
    SDL_Rect tileset[NUM_TILES];
    SDL_Renderer *renderer;
    int cur_sprite;
}player_t;

void update_player(map_t *map, player_t *player);
void handle_input(SDL_Event event, game_t *game, player_t *player, map_t *map);
player_t *initialize_player(const char *filename, SDL_Renderer *renderer, int x, int y);

#endif 
