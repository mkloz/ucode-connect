#ifndef MYEZIK_COLLIDER_H
#define MYEZIK_COLLIDER_H

#include "common.h"

typedef struct s_collider {
    SDL_Point p1;
    SDL_Point p2;
    SDL_Point p3;
    SDL_Point p4;
} t_collider;

void collider_render(t_collider *collider_ptr, SDL_Renderer *rend_ptr);
t_collider empty_collider();
void collider_init(t_collider *collider_ptr, SDL_Rect *rect, double angle);
bool collider_contains(t_collider *collider_ptr, SDL_Point *point_ptr);
bool collider_contact(t_collider *collider1_ptr, t_collider *collider2_ptr);
#endif
