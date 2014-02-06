#ifndef TOWER_H
#define TOWER_h

#include <SDL2/SDL.h>

#include "graphics.h"

#define report_error(ret) fprintf(stderr, "%s [%s():%d]: %s\n", __FILE__, __FUNCTION__, \
        __LINE__ - 1, SDL_GetError()); \
    SDL_ClearError();

#define img_report_error(ret) fprintf(stderr, "%s [%s():%d]: %s\n", __FILE__, __FUNCTION__, \
        __LINE__ - 1, IMG_GetError());


typedef struct game_t{
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
}game_t;

bool debug;

bool get_random_bool(void);
int get_random_int(int bottom, int top);
void main_game_loop(game_t *game);
game_t *init_game(void);
void cleanup(game_t *game);

#endif
