#include "../inc/soldier.h"
#include "../inc/bullet.h"

void soldier_init(t_soldier *soldier_ptr) {
    soldier_ptr->texture = get_resources()->soldier_texture;
    soldier_ptr->pos.x = WIDTH / 2;
    soldier_ptr->pos.y = HEIGHT / 2;
    soldier_ptr->angle = 0;
    soldier_ptr->collider = empty_collider();
    soldier_ptr->kills = 0;
    SDL_Rect rect = soldier_get_rect(soldier_ptr);
    collider_init(&soldier_ptr->collider, &rect, 0);

    soldier_ptr->bullets = NULL;
}

SDL_Rect soldier_get_rect(t_soldier *soldier_ptr) {
    int xPos = soldier_ptr->pos.x;
    int yPos = soldier_ptr->pos.y;

    SDL_Rect dest = {xPos - (SOLDIER_WIDTH / 2),
                     yPos - (SOLDIER_HEIGHT / 2),
                     SOLDIER_WIDTH, SOLDIER_HEIGHT};
    return dest;
}

void draw_counter(int count, SDL_Renderer *renderer_ptr) {
    char kills_text[16];

    memset(kills_text, 0, 16);
    sprintf(kills_text, "%d", count);

    SDL_Rect pos = {5, 5, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(get_resources()->font, kills_text, YELLOW);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_ptr, surface);

    SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);

    SDL_RenderCopy(renderer_ptr, texture, NULL, &pos);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void soldier_render(t_soldier *soldier_ptr, SDL_Renderer *renderer_ptr) {
    SDL_Rect soldierRect = soldier_get_rect(soldier_ptr);

    SDL_RenderCopyEx(renderer_ptr, soldier_ptr->texture, NULL,
                     &soldierRect, soldier_ptr->angle, NULL, SDL_FLIP_NONE);
    collider_render(&soldier_ptr->collider, renderer_ptr);

    if (!soldier_ptr->bullets)
        return;
    for (t_list *temp = soldier_ptr->bullets; temp != NULL; temp = temp->next)
        bullet_render((t_bullet *) temp->data, renderer_ptr);
}

void soldier_handle_event(t_soldier *soldier_ptr, SDL_Event *event_ptr) {
    switch (event_ptr->type) {
        case SDL_MOUSEMOTION: {
            SDL_Point mouse = {event_ptr->motion.x, event_ptr->motion.y};
            SDL_Point position = {soldier_ptr->pos.x, soldier_ptr->pos.y};

            soldier_ptr->angle = angle_of(position, mouse);
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            Mix_PlayChannel(-1, get_resources()->shot_chunk, 0);

            mx_push_back(&soldier_ptr->bullets, (void *) bullet_generate(soldier_ptr));
            break;
        }
        case SDL_KEYDOWN: {
            SDL_Keycode key = event_ptr->key.keysym.sym;

            if (key == SDLK_w
                || key == SDLK_a
                || key == SDLK_s
                || key == SDLK_d) {
                soldier_ptr->moving = true;
                soldier_ptr->direction = key;
            }

            break;
        }
        case SDL_KEYUP: {
            if (event_ptr->key.keysym.sym == soldier_ptr->direction)
                soldier_ptr->moving = false;
        }
        default:
            break;
    }
}

void soldier_move(t_soldier *soldier_ptr) {
    SDL_Point new_pos = soldier_ptr->pos;
    t_level *level = get_level_setting_ptr();
    switch (soldier_ptr->direction) {
        case SDLK_w:
            new_pos.x += get_offset_x(level->soldier_speed, soldier_ptr->angle);
            new_pos.y += get_offset_y(level->soldier_speed, soldier_ptr->angle);
            break;
        case SDLK_s:
            new_pos.x += get_offset_x(level->soldier_speed, soldier_ptr->angle - 180);
            new_pos.y += get_offset_y(level->soldier_speed, soldier_ptr->angle - 180);
            break;
        case SDLK_d:
            new_pos.x += get_offset_x(level->soldier_speed, soldier_ptr->angle + 90);
            new_pos.y += get_offset_y(level->soldier_speed, soldier_ptr->angle + 90);
            break;
        case SDLK_a:
            new_pos.x += get_offset_x(level->soldier_speed, soldier_ptr->angle - 90);
            new_pos.y += get_offset_y(level->soldier_speed, soldier_ptr->angle - 90);
            break;
        default:
            break;
    }

    static SDL_Rect window = {0, 0, WIDTH, HEIGHT};

    if (point_in_rect(new_pos, window))
        soldier_ptr->pos = new_pos;
}

void soldier_handle_tick(t_soldier *soldier_ptr, t_zombie_list *zombies) {
    if (soldier_ptr->moving)
        soldier_move(soldier_ptr);

    SDL_Rect soldierRect = soldier_get_rect(soldier_ptr);

    collider_init(&soldier_ptr->collider, &soldierRect, soldier_ptr->angle);

    for (t_list *temp = soldier_ptr->bullets; temp != NULL; temp = temp->next)
        bullet_handle_tick((t_bullet *) temp->data, zombies, soldier_ptr);
}
