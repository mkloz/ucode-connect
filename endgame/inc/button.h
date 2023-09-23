#ifndef MYEZIK_BUTTON_H
#define MYEZIK_BUTTON_H

#include "common.h"
#include "resourses.h"
#include "menu.h"

typedef struct s_button {
    SDL_Rect rect;
    SDL_Texture *texture;
} t_button;

void button_init(t_button *button_ptr);
void button_render(t_button *button_ptr, SDL_Renderer *renderer_ptr);
void button_handle_event(t_button *p_button, SDL_Event *event_ptr);
#endif
