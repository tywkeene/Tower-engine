#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tower.h"
#include "graphics.h"
#include "player.h"
#include "map.h"

void update_player(map_t *map, player_t *player)
{
    map_tile_t *tile;
    SDL_Rect rect;
    if((tile = pixel_to_tile(map, player->rect.x, player->rect.y)) == NULL){
        SDL_RenderCopy(player->renderer, player->texture, 
                &player->tileset[player->cur_sprite], &player->last);
        return;
    }
    rect.x = tile->x;
    rect.y = tile->y;
    if(SDL_HasIntersection(&player->rect, &rect) == SDL_TRUE && tile->passable == 0)
        player->rect = player->last;
    SDL_RenderCopy(player->renderer, player->texture, 
            &player->tileset[player->cur_sprite], &player->rect);
}

void handle_input(SDL_Event event, game_t *game, player_t *player, map_t *map)
{
    switch(event.type){
        case SDL_QUIT:
            game->running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_q)
                game->running = false;
            player->last = player->rect;
            if(event.key.keysym.sym == SDLK_DOWN)
                player->rect.y += TILE_SIZE;
            if(event.key.keysym.sym == SDLK_UP)
                player->rect.y -= TILE_SIZE;
            if(event.key.keysym.sym == SDLK_RIGHT)
                player->rect.x += TILE_SIZE;
            if(event.key.keysym.sym == SDLK_LEFT)
                player->rect.x -= TILE_SIZE;
            if(event.key.keysym.sym == SDLK_F1 && debug == 1){
                fprintf(stdout, "(%d,%d)\n", player->rect.x / TILE_SIZE, player->rect.y / TILE_SIZE);
            }
            break;
        default:
            break;
    }
}

player_t *initialize_player(const char *filename, SDL_Renderer *renderer, int x, int y)
{
    player_t *player = malloc(sizeof(player_t));
    player->rect.h = TILE_SIZE;
    player->rect.w = TILE_SIZE;
    player->rect.x = WIN_WIDTH / 2 - TILE_SIZE;
    player->rect.y = WIN_HEIGHT / 2 - TILE_SIZE;
    player->last = player->rect;

    player->renderer = renderer;
    player->cur_sprite = 1;
    player->texture = initialize_texture(player->renderer, filename);
    get_tileset(player->tileset);
    return player;
}

