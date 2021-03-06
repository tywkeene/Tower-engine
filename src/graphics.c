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
#include "map.h"

SDL_Texture *initialize_texture(game_t *game, SDL_Renderer *renderer, const char *filename)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if(texture == NULL)
		img_report_error(NULL);

	fprintf(stdout, "Loaded texture: %s\n", filename);

	return texture;
}

void get_tileset(game_t *game, SDL_Rect set[NUM_TILES])
{
	int i;
	int x = 0, y = 0;

	fprintf(stdout, "Tilesheet dimensions:%dx%d\n", TILE_SHEET_WIDTH, TILE_SHEET_HEIGHT);
	fprintf(stdout, "\tTile dimensions: %dx%d\n", TILE_HEIGHT, TILE_WIDTH);
	fprintf(stdout, "\tTiles in a sheet: %d\n\n", NUM_TILES);

	for(i = 0; i < NUM_TILES; i++){
		set[i].x = x;
		set[i].y = y;
		set[i].w = TILE_WIDTH;
		set[i].h = TILE_HEIGHT;
		if(x == (TILE_SHEET_WIDTH - TILE_WIDTH)){
			y += TILE_WIDTH;
			x = 0;
			continue;
		}
		x += TILE_HEIGHT;
	}
	return;
}

int initialize_graphics(void)
{
	int flags = GFX_INIT_FLAGS;
	int ret;

	ret = IMG_Init(flags);
	if((ret & flags) != flags)
		img_report_error();
	return ret;
}
