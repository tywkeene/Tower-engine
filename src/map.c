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

map_tile_t *initialize_tile(bool pass, int sprite, int x, int y)
{
    map_tile_t *tile = malloc(sizeof(map_tile_t));
    if(debug)
        tile->passable = 1;
    else
        tile->passable = pass;
    tile->sprite = sprite;
    tile->x = x;
    tile->y = y;
    return tile;
}

map_tile_t *pixel_to_tile(map_t *map, int x, int y)
{
    return map->tiles[x / TILE_SIZE][y / TILE_SIZE];
}

void tile_to_pixel(int x, int y, int result[2])
{
    result[0] = (x * TILE_SIZE);
    result[1] = (y * TILE_SIZE);
}

bool check_intersect(int count, room_t *room, room_t **list)
{
    int i;
    SDL_Rect one, two;
    one.x = room->x;
    one.y = room->y;
    one.w = room->w;
    one.h = room->h;
    for(i = 0; i < count; i++){
        two.x = list[i]->x;
        two.y = list[i]->y;
        two.w = list[i]->w + 1;
        two.h = list[i]->h + 1;
        if(SDL_HasIntersection(&one, &two) == SDL_TRUE)
            return 1;
    }
    return 0;
}

room_t *place_room(int count, room_t **list)
{
    int i;
    room_t *room = malloc(sizeof(room_t));

    room->x = get_random_int(ROOM_MIN_SIZE, MAP_WIDTH - 2);
    room->y = get_random_int(ROOM_MIN_SIZE, MAP_HEIGHT - 2);
    room->w = get_random_int(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
    room->h = get_random_int(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
    if(count)
        while(check_intersect(count, room, list) != 0){
            fprintf(stdout, "Found intersection, moving room\n");
            room->x = get_random_int(ROOM_MIN_SIZE, MAP_WIDTH - 2);
            room->y = get_random_int(ROOM_MIN_SIZE, MAP_HEIGHT - 2);
            count--;
        }
    if(debug){
        fprintf(stdout, "Room %d: (%d,%d) %dx%d\n", count, room->x, room->y, room->w, room->h);
        fprintf(stdout, "\t%d total tiles\n", room->w + room->h);
    }
    return room;
}

void fill_room(map_t *map, room_t *room)
{
    int i, j;
    int x, y;
    int w, h;
    int tile_x, tile_y;
    w = room->w;
    h = room->h;
    x = room->x;
    y = room->y;

    room->tiles = malloc(sizeof(map_tile_t *) * w);
    for(i = 0; i < w; i++)
        room->tiles[i] = malloc(sizeof(map_tile_t *) * h);

    for(i = 0, tile_x = x; i < w && tile_x > 0; i++, tile_x--){
        for(j = 0, tile_y = y; j < h && tile_y > 0; j++, tile_y--){
            room->tiles[i][j] = map->tiles[tile_x][tile_y];
            room->tiles[i][j]->passable = 1;
            room->tiles[i][j]->sprite = 4;
        }
    }
}

room_t **generate_rooms(int count, map_t *map)
{
    int i;
    bool done;
    room_t **list = malloc(sizeof(room_t *) * count);
    room_t *room;
    fprintf(stdout, "Generating %d rooms...\n", count);
    for(i = 0; i < count; i++){
        list[i] = place_room(i, list);
        fill_room(map, list[i]);
    }
    return list;
}

map_t *initialize_map(SDL_Renderer *renderer, const char *texture_filename)
{
    int i, j;
    int x, y;
    map_t *map = malloc(sizeof(map_t));
    map->renderer = renderer;
    map->texture = initialize_texture(map->renderer, texture_filename);
    get_tileset(map->tileset);

    for(i = 0, x = 0; i < WIN_WIDTH / TILE_SIZE && x < WIN_WIDTH; i++, x += TILE_SIZE){
        for(j = 0, y = 0; j < WIN_HEIGHT / TILE_SIZE && y < WIN_HEIGHT; j++, y += TILE_SIZE){
            map->tiles[i][j] = malloc(sizeof(map_tile_t));
            map->tiles[i][j] = initialize_tile(0, -1, x, y);
        }
    }
    fprintf(stdout, "Initialized map with dimensions (in tiles): %dx%d\n", 
            (WIN_WIDTH / TILE_SIZE), (WIN_HEIGHT / TILE_SIZE));
    fprintf(stdout, "\t%d total tiles\n", 
            (WIN_WIDTH / TILE_SIZE) + (WIN_HEIGHT / TILE_SIZE));
    /*
    map->room_count = get_random_int(MIN_ROOMS, MAX_ROOMS);
    map->rooms = generate_rooms(map->room_count, map);
    */

    return map;
}

void draw_map(map_t *map)
{
    SDL_Rect rect;
    int i, j, r;
    int sprite;
    for(i = 0; i < WIN_WIDTH / TILE_SIZE; i++){
        for(j = 0; j < WIN_HEIGHT / TILE_SIZE; j++){
            rect.h = TILE_SIZE;
            rect.w = TILE_SIZE;
            rect.x = map->tiles[i][j]->x;
            rect.y = map->tiles[i][j]->y;
            sprite = map->tiles[i][j]->sprite;
            if(SDL_RenderCopy(map->renderer, map->texture, &map->tileset[sprite], &rect) != 0)
                report_error();
        }
    }
}
