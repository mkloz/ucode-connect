#ifndef MYEZIK_BULLET_H
#define MYEZIK_BULLET_H

#include "common.h"
#include "collider.h"
#include "resourses.h"
#include "soldier.h"

#define BULLET_NORMAL_DAMAGE 50
#define BULLET_COOL_DAMAGE 60

#define BULLET_WIDTH 20
#define BULLET_HEIGHT 10
#define BULLET_SPEED 20
#define BULLET_INDENT 60
#define BULLET_OFFSET 25

typedef struct s_bullet {
    SDL_Texture *texture;
    SDL_Point pos;
    t_collider collider;
    int angle;
    bool is_valid;
    int damage;
} t_bullet;

void bullet_init(t_bullet *bullet_ptr);
SDL_Rect bullet_get_rect(t_bullet *bullet_ptr);
void bullet_render(t_bullet *bullet_ptr, SDL_Renderer *renderer_ptr);
void bullet_handle_tick(t_bullet *bullet_ptr, t_zombie_list *zombies, t_soldier *soldier_ptr);
t_bullet *bullet_generate(t_soldier *soldier_ptr);
bool bullet_is_invalid(t_bullet *bullet_ptr);

#endif
