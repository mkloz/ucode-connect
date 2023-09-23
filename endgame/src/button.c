#include "../inc/button.h"

void button_init(t_button *button_ptr) {
    button_ptr->texture = get_resources()->pause_button;
    int w = 50;
    int h = 50;
    SDL_Rect rect = {WIDTH - w, 0, w, h};
    button_ptr->rect = rect;
}

void button_render(t_button *button_ptr, SDL_Renderer *renderer_ptr) {
    SDL_RenderCopy(renderer_ptr, button_ptr->texture, NULL, &button_ptr->rect);
}

void button_handle_event(t_button *p_button, SDL_Event *event_ptr) {
    switch (event_ptr->type) {
        case SDL_MOUSEBUTTONDOWN: {
            SDL_Point mouse = {event_ptr->motion.x, event_ptr->motion.y};

            if (point_in_rect(mouse, p_button->rect)) {
                throw_user_event(GAME_STATE_PAUSE);
            }
        }
    }
}
