#ifndef MYEZIK_RESOURSES_H
#define MYEZIK_RESOURSES_H

#include "common.h"

typedef struct s_resources {
    SDL_Texture *soldier_texture;
    SDL_Texture *zombie_texture;
    SDL_Texture *zombie2_texture;
    SDL_Texture *bullet_texture;
    SDL_Texture *bullet2_texture;
    SDL_Texture *background_texture1;
    SDL_Texture *background_texture2;
    SDL_Texture *background_texture3;
    SDL_Texture *pause_menu;
    SDL_Texture *pause_button;
    TTF_Font *font;

    Mix_Chunk *shot_chunk;
    Mix_Chunk *death_chunk;
    Mix_Chunk *game_over_chunk;
} t_resources;

t_resources *get_resources();
void resources_init(SDL_Renderer *renderer);
void resources_destroy();

#endif
