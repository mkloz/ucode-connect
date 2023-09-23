#include "../inc/resourses.h"
#include "../inc/menu.h"
#include "../inc/levels.h"

void resources_init(SDL_Renderer *renderer) {
    t_resources *resources_ptr = get_resources();

    resources_ptr->soldier_texture = load_texture_from_file("resource/img/soldier.png", renderer);
    resources_ptr->zombie_texture = load_texture_from_file("resource/img/zombie.png", renderer);
    resources_ptr->zombie2_texture = load_texture_from_file("resource/img/zombie2.png", renderer);
    resources_ptr->bullet_texture = load_texture_from_file("resource/img/bullet.png", renderer);
    resources_ptr->bullet2_texture = load_texture_from_file("resource/img/bullet2.png", renderer);
    resources_ptr->background_texture1 = load_texture_from_file("resource/maps/map1.png", renderer);
    resources_ptr->background_texture2 = load_texture_from_file("resource/maps/map2.png", renderer);
    resources_ptr->background_texture3 = load_texture_from_file("resource/maps/map3.png", renderer);
    resources_ptr->pause_menu = load_texture_from_file("resource/img/pause_menu.png", renderer);
    resources_ptr->pause_button = load_texture_from_file("resource/img/pause_button.png", renderer);
    resources_ptr->font = TTF_OpenFont("resource/fonts/ShortBaby.ttf", MENU_FONT_SIZE);

    resources_ptr->shot_chunk = Mix_LoadWAV("resource/sounds/shot.wav");
    resources_ptr->death_chunk = Mix_LoadWAV("resource/sounds/zombie-death.wav");
    resources_ptr->game_over_chunk = Mix_LoadWAV("resource/sounds/game-over.wav");
}

void resources_destroy() {
    t_resources *resources_ptr = get_resources();

    Mix_FreeChunk(resources_ptr->shot_chunk);
    Mix_FreeChunk(resources_ptr->death_chunk);
    Mix_FreeChunk(resources_ptr->game_over_chunk);

    SDL_DestroyTexture(resources_ptr->soldier_texture);
    SDL_DestroyTexture(resources_ptr->zombie_texture);
    SDL_DestroyTexture(resources_ptr->zombie2_texture);
    SDL_DestroyTexture(resources_ptr->bullet_texture);
    SDL_DestroyTexture(resources_ptr->bullet2_texture);
    SDL_DestroyTexture(resources_ptr->background_texture1);
    SDL_DestroyTexture(resources_ptr->background_texture2);
    SDL_DestroyTexture(resources_ptr->background_texture3);
    SDL_DestroyTexture(resources_ptr->pause_menu);
    SDL_DestroyTexture(resources_ptr->pause_button);

    TTF_CloseFont(resources_ptr->font);
}

t_resources *get_resources(void) {
    static t_resources resources;

    return &resources;
}
