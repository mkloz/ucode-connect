#include "../inc/bullet.h"
#include "../inc/zombie.h"

void bullet_init(t_bullet *bullet_ptr) {
    bool cool_bullet = rand() % 2;

    bullet_ptr->damage = cool_bullet ? BULLET_COOL_DAMAGE : BULLET_NORMAL_DAMAGE;
    bullet_ptr->texture = cool_bullet ?
                          get_resources()->bullet_texture :
                          get_resources()->bullet2_texture;
    bullet_ptr->angle = 0;
    bullet_ptr->pos.x = 0;
    bullet_ptr->pos.y = 0;
    bullet_ptr->is_valid = true;

    SDL_Rect rect = bullet_get_rect(bullet_ptr);
    collider_init(&bullet_ptr->collider, &rect, bullet_ptr->angle);
}

SDL_Rect bullet_get_rect(t_bullet *bullet_ptr) {
    int xPos = bullet_ptr->pos.x;
    int yPos = bullet_ptr->pos.y;

    static const int xSize = BULLET_WIDTH;
    static const int ySize = BULLET_HEIGHT;

    SDL_Rect dest = {xPos - (xSize / 2), yPos - (ySize / 2), xSize, ySize};
    return dest;
}

void bullet_render(t_bullet *bullet_ptr, SDL_Renderer *renderer_ptr) {
    if (!bullet_ptr->is_valid)
        return;

    SDL_Rect rect = bullet_get_rect(bullet_ptr);

    SDL_RenderCopyEx(renderer_ptr, bullet_ptr->texture, NULL,
                     &rect, bullet_ptr->angle, NULL, SDL_FLIP_NONE);
    collider_render(&bullet_ptr->collider, renderer_ptr);
}

void bullet_handle_tick(t_bullet *bullet_ptr, t_zombie_list *zombies, t_soldier *soldier_ptr) {
    if (!bullet_ptr->is_valid)
        return;
    SDL_Rect window = {0, 0, WIDTH, HEIGHT};

    if (!point_in_rect(bullet_ptr->pos, window))
        bullet_ptr->is_valid = false;

    bullet_ptr->pos.x = bullet_ptr->pos.x + get_offset_x(BULLET_SPEED, bullet_ptr->angle);
    bullet_ptr->pos.y = bullet_ptr->pos.y + get_offset_y(BULLET_SPEED, bullet_ptr->angle);

    SDL_Rect rect = bullet_get_rect(bullet_ptr);

    collider_init(&bullet_ptr->collider, &rect, bullet_ptr->angle);

    for (t_list *zombie_node = zombies->list; zombie_node != NULL; zombie_node = zombie_node->next) {
        t_zombie *zombie = (t_zombie *) zombie_node->data;

        if (collider_contact(&zombie->collider, &bullet_ptr->collider)) {
            bullet_ptr->is_valid = false;
            zombie_handle_hit(zombie, bullet_ptr, soldier_ptr, &zombies->list_size);
        }
    }
}

t_bullet *bullet_generate(t_soldier *soldier_ptr) {
    t_bullet *bullet = malloc(sizeof(t_bullet));

    bullet_init(bullet);

    bullet->angle = soldier_ptr->angle;
    bullet->pos.x = soldier_ptr->pos.x + get_offset_x(BULLET_INDENT, bullet->angle);
    bullet->pos.y = soldier_ptr->pos.y + get_offset_y(BULLET_INDENT, bullet->angle);

    bullet->pos.x += get_offset_x(BULLET_OFFSET, bullet->angle + 90);
    bullet->pos.y += get_offset_y(BULLET_OFFSET, bullet->angle + 90);

    return bullet;
}

bool bullet_is_invalid(t_bullet *bullet_ptr) {
    return !bullet_ptr->is_valid;
}
