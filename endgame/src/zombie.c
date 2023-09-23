#include "../inc/zombie.h"

void zombie_init(t_zombie *zombie_ptr) {
    bool cool_zombie = rand() % 2;

    zombie_ptr->health = cool_zombie ? ZOMBIE_HEALTH_BIG : ZOMBIE_HEALTH_NORMAL;
    zombie_ptr->texture = cool_zombie ? get_resources()->zombie_texture : get_resources()->zombie2_texture;
    zombie_ptr->angle = 0;
    zombie_ptr->pos.x = 50;
    zombie_ptr->pos.y = 100;
    zombie_ptr->collider = empty_collider();
    zombie_ptr->is_alive = true;
    SDL_Rect rect = zombie_get_rect(zombie_ptr);
    collider_init(&zombie_ptr->collider, &rect, 0);
}

void zombie_render(t_zombie *zombie_ptr, SDL_Renderer *rend_ptr) {
    if (!zombie_ptr->is_alive)
        return;

    SDL_Rect zombieRect = zombie_get_rect(zombie_ptr);
    SDL_RenderCopyEx(rend_ptr, zombie_ptr->texture, NULL,
                     &zombieRect, zombie_ptr->angle, NULL, SDL_FLIP_NONE);
    collider_render(&zombie_ptr->collider, rend_ptr);
}

SDL_Rect zombie_get_rect(t_zombie *zombie_ptr) {
    int xPos = zombie_ptr->pos.x;
    int yPos = zombie_ptr->pos.y;

    int size = 85 * zombie_ptr->health / ZOMBIE_HEALTH_NORMAL;

    if (size < 85)
        size = 85;

    SDL_Rect dest = {xPos - (size / 2), yPos - (size / 2), size, size};
    return dest;
}

void zombie_handle_tick(t_zombie *zombie_ptr, t_soldier *soldier_ptr) {
    if (!zombie_ptr->is_alive)
        return;

    if (collider_contact(&zombie_ptr->collider, &soldier_ptr->collider)) {
        throw_user_event(GAME_EVENT_SOLDIER_DEAD);
        Mix_PlayChannel(-1, get_resources()->game_over_chunk, 0);
        return;
    }

    zombie_ptr->angle = angle_of(zombie_ptr->pos, soldier_ptr->pos);

    zombie_set_position(zombie_ptr,
                        zombie_ptr->pos.x + get_offset_x(
                                get_level_setting_ptr()->zombie_speed,
                                zombie_ptr->angle),
                        zombie_ptr->pos.y + get_offset_y(
                                get_level_setting_ptr()->zombie_speed,
                                zombie_ptr->angle));

    SDL_Rect zombieRect = zombie_get_rect(zombie_ptr);
    collider_init(&zombie_ptr->collider, &zombieRect, zombie_ptr->angle);
}

void zombie_set_position(t_zombie *zombie_ptr, int x, int y) {
    zombie_ptr->pos.x = x;
    zombie_ptr->pos.y = y;

    SDL_Rect rect = zombie_get_rect(zombie_ptr);
    collider_init(&zombie_ptr->collider, &rect, 0);
}

t_zombie *zombie_generate(void) {
    t_zombie *zombie = malloc(sizeof(t_zombie));

    zombie_init(zombie);
    int x;
    int y;

    switch ((int) get_random_num(0, 3)) {
        case 0:
            x = get_random_num(-ZOMBIE_WIDTH / 2, WIDTH + ZOMBIE_WIDTH / 2);
            y = -ZOMBIE_HEIGHT / 2;
            break;
        case 1:
            x = WIDTH + ZOMBIE_WIDTH / 2;
            y = get_random_num(-ZOMBIE_HEIGHT / 2, HEIGHT + ZOMBIE_HEIGHT / 2);
            break;
        case 2:
            x = get_random_num(-ZOMBIE_WIDTH / 2, WIDTH + ZOMBIE_WIDTH / 2);
            y = HEIGHT + ZOMBIE_HEIGHT / 2;
            break;
        case 3:
            x = -ZOMBIE_WIDTH / 2;
            y = get_random_num(-ZOMBIE_HEIGHT / 2, HEIGHT + ZOMBIE_HEIGHT / 2);
            break;
    }

    zombie_set_position(zombie, x, y);

    return zombie;
}

bool zombie_is_dead(t_zombie *zombie_ptr) {
    return !zombie_ptr->is_alive;
}

void zombie_handle_hit(t_zombie *zombie_ptr, t_bullet *bullet_ptr, t_soldier *soldier_ptr, int *count) {
    zombie_ptr->health -= bullet_ptr->damage;

    if (zombie_ptr->health <= 0) {
        zombie_ptr->is_alive = false;
        (*count)--;
        ++soldier_ptr->kills;
        Mix_PlayChannel(-1, get_resources()->death_chunk, 0);
    }
}
