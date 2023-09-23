#ifndef MYEZIK_SOLDIER_H
#define MYEZIK_SOLDIER_H

#include "common.h"
#include "collider.h"
#include "resourses.h"
#include "menu.h"
#include "levels.h"

#define  SOLDIER_WIDTH 100
#define  SOLDIER_HEIGHT 75

typedef struct s_soldier {
    SDL_Texture *texture;
    SDL_Point pos;
    double angle;
    t_collider collider;
    t_list *bullets;
    int direction;
    bool moving;
    int kills;
} t_soldier;

void soldier_init(t_soldier *soldier_ptr);
void soldier_render(t_soldier *soldier_ptr, SDL_Renderer *renderer_ptr);
void soldier_handle_event(t_soldier *soldier_ptr, SDL_Event *event_ptr);
SDL_Rect soldier_get_rect(t_soldier *soldier_ptr);
void soldier_handle_tick(t_soldier *soldier_ptr, t_zombie_list *zombies);
void draw_counter(int count, SDL_Renderer *renderer_ptr);
#endif
