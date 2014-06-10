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
#include "cursor.h"
#include "map.h"

void update_cursor(game_t *game)
{
	SDL_WarpMouseInWindow(game->window, game->cursor->rect.x,
			game->cursor->rect.y);
	SDL_RenderCopy(game->cursor->renderer, game->cursor->texture, 
			&game->cursor->tileset[game->cursor->cur_sprite],
			&game->cursor->rect);
	return;
}

void destroy_camera(camera_t *camera)
{
	free(camera);
	return;
}

camera_t *initialize_camera(game_t *game, int x, int y, int speed)
{
	camera_t *camera = malloc(sizeof(camera_t));

	camera->rect.x = x;
	camera->rect.y = y;

	camera->speed = speed;

	print_coords("Initialized camera position", x, y);
	return camera;
}

void camera_goto(game_t *game, int x, int y)
{
	game->camera->rect.x = x;
	game->camera->rect.y = y;
	return;
}

void do_camera_scroll(game_t *game, int x, int y)
{
	if(x < TILE_WIDTH)
		game->camera->rect.x -= TILE_WIDTH_HALF/2;
	else if(x > (WIN_WIDTH - TILE_WIDTH))
		game->camera->rect.x += TILE_WIDTH_HALF/2;

	if(y < TILE_HEIGHT)
		game->camera->rect.y -= TILE_HEIGHT_HALF/2;
	else if(y > (WIN_HEIGHT - TILE_HEIGHT))
		game->camera->rect.y += TILE_HEIGHT_HALF/2;

	game->cursor->rect.x = x;
	game->cursor->rect.y = y;
	update_cursor(game);
	return;
}

void handle_input(SDL_Event event, game_t *game)
{
	int x, y;
	map_tile_t *tile;
	SDL_GetMouseState(&x, &y);

	switch(event.type){
	case SDL_QUIT:
		game->running = false;
		break;
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE)
			game->running = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		tile = screen_to_grid(game, x, y);
		if(tile)
			tile->sprite = -1;
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	case SDL_MOUSEMOTION:
		update_cursor(game);
		do_camera_scroll(game, x, y);
		break;
	default:
		break;
	}
	return;
}

void destroy_cursor(cursor_t *cursor)
{
	SDL_DestroyRenderer(cursor->renderer);
	free(cursor);
	return;
}

cursor_t *initialize_cursor(game_t *game, const char *filename, SDL_Renderer *renderer, int x, int y)
{
	cursor_t *cursor = malloc(sizeof(cursor_t));
	cursor->rect.h = CURSOR_HEIGHT;
	cursor->rect.w = CURSOR_WIDTH;
	cursor->rect.x = x;
	cursor->rect.y = y;
	cursor->last = cursor->rect;

	cursor->renderer = renderer;
	cursor->cur_sprite = 0;
	cursor->texture = initialize_texture(game, cursor->renderer, filename);
	get_tileset(game, cursor->tileset);
	print_coords("Initialized cursor position", x, y);
	return cursor;
}
