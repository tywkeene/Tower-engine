#ifndef TOWER_H
#define TOWER_h

#include <SDL2/SDL.h>

#define report_error(ret) fprintf(stderr, "%s [%s():%d]: %s\n", __FILE__, __FUNCTION__, \
        __LINE__ - 1, SDL_GetError()); \
    SDL_ClearError();

#define img_report_error(ret) fprintf(stderr, "%s [%s():%d]: %s\n", __FILE__, __FUNCTION__, \
        __LINE__ - 1, IMG_GetError());

#define print_coords(msg, x, y) if(msg != NULL){ fprintf(stdout, "%s: (%d,%d)\n", msg, x, y); } \
	else{ fprintf(stdout, "(%d,%d)", x, y); }

typedef struct game_t{
	bool debug;
	struct cursor_t *cursor;
	struct map_t *map;
	struct camera_t *camera;
	bool running;
	SDL_Window *window;
	SDL_Renderer *renderer;
}game_t;


void cap_frame_rate(void);
void main_game_loop(game_t *game);
game_t *initialize_game(void);
void cleanup(game_t *game);

#endif
