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

int camera_x = WIN_WIDTH / TILE_WIDTH / 2;
int camera_y = WIN_HEIGHT / TILE_HEIGHT / 2;

void update_player(map_t *map, player_t *player)
{
	SDL_RenderCopy(player->renderer, player->texture, 
			&player->tileset[player->cur_sprite], &player->rect);
}

void handle_input(SDL_Event event, game_t *game, player_t *player, map_t *map)
{
	map_tile_t *tile;
	int x, y;

	switch(event.type){
	case SDL_QUIT:
		game->running = false;
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);

		if(x < 10)
			camera_x -= 2;
		else if(x > (WIN_WIDTH - 10))
			camera_x += 2;

		if(y < 10)
			camera_y -= 2;
		else if(y > (WIN_HEIGHT - 10))
			camera_y += 2;

		player->rect.y = y;
		player->rect.x = x;
		break;
	default:
		break;
	}
}

player_t *initialize_player(const char *filename, SDL_Renderer *renderer, int x, int y)
{
	player_t *player = malloc(sizeof(player_t));
	player->rect.h = 5;
	player->rect.w = 5;
	player->rect.x = x;
	player->rect.y = y;
	player->last = player->rect;

	player->renderer = renderer;
	player->cur_sprite = 0;
	player->texture = initialize_texture(player->renderer, filename);
	get_tileset(player->tileset);
	return player;
}

