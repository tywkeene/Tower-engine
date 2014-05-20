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
	SDL_RenderCopy(game->cursor->renderer, game->cursor->texture, 
			&game->cursor->tileset[game->cursor->cur_sprite],
			&game->cursor->rect);
	SDL_WarpMouseInWindow(game->window, game->camera->rect.x,
			game->camera->rect.y);
}

camera_t *initialize_camera(int x, int y, int speed)
{
	camera_t *camera = malloc(sizeof(camera_t));

	camera->rect.x = x;
	camera->rect.y = y;

	camera->speed = speed;

	return camera;
}

void do_camera_scroll(game_t *game, int x, int y)
{
	if(x <= 5)
		game->camera->rect.x -= game->camera->speed;
	else if(x >= (WIN_WIDTH - 10))
		game->camera->rect.x += game->camera->speed;

	if(y <= 5)
		game->camera->rect.y -= game->camera->speed;
	else if(y >= (WIN_HEIGHT - 10))
		game->camera->rect.y += game->camera->speed;

	game->cursor->rect.x = x;
	game->cursor->rect.y = y;
}

void handle_input(SDL_Event event, game_t *game)
{
	int x, y;

	SDL_GetMouseState(&x, &y);

	switch(event.type){
	case SDL_QUIT:
		game->running = false;
		break;
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_q)
			game->running = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		fprintf(stdout, "(%d,%d)\n", x, y);
		break;
	case SDL_MOUSEBUTTONUP:
		break;

	case SDL_MOUSEMOTION:
		do_camera_scroll(game, x, y);
		break;
	default:
		break;
	}
}

cursor_t *initialize_cursor(const char *filename, SDL_Renderer *renderer, int x, int y)
{
	cursor_t *cursor = malloc(sizeof(cursor_t));
	cursor->rect.h = 32;
	cursor->rect.w = 64;
	fprintf(stdout, "(%d,%d)\n", x, y);
	cursor->rect.x = x;
	cursor->rect.y = y;
	cursor->last = cursor->rect;

	cursor->renderer = renderer;
	cursor->cur_sprite = 0;
	cursor->texture = initialize_texture(cursor->renderer, filename);
	get_tileset(cursor->tileset);
	return cursor;
}

