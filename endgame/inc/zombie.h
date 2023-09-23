#ifndef MYEZIK_ZOMBIE_H
#define MYEZIK_ZOMBIE_H

#include "common.h"
#include "collider.h"
#include "resourses.h"
#include "bullet.h"
#include "soldier.h"
#include "levels.h"

#define ZOMBIE_HEALTH_NORMAL 50
#define ZOMBIE_HEALTH_BIG 60
#define ZOMBIE_WIDTH 100
#define ZOMBIE_HEIGHT 100

typedef struct s_zombie {
    SDL_Texture *texture;
    SDL_Point pos;
    double angle;
    t_collider collider;
    bool is_alive;
    int health;
} t_zombie;

void zombie_init(t_zombie *zombie_ptr);
void zombie_render(t_zombie *zombie_ptr, SDL_Renderer *rend_ptr);
void zombie_handle_tick(t_zombie *zombie_ptr, t_soldier *soldier_ptr);
void zombie_set_position(t_zombie *zombie_ptr, int x, int y);
SDL_Rect zombie_get_rect(t_zombie *zombie_ptr);
t_zombie *zombie_generate(void);
bool zombie_is_dead(t_zombie *zombie_ptr);
void zombie_handle_hit(t_zombie *zombie_ptr, t_bullet *bullet_ptr, t_soldier *soldier_ptr, int *count);

#endif
