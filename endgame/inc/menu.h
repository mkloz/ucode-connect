#ifndef MYEZIK_START_MENU_H
#define MYEZIK_START_MENU_H

#include "common.h"
#include "resourses.h"

#define MENU_FONT_SIZE 48
#define MENU_ITEM_PADDING 20
typedef struct t_menu_item_initializer {
    char *text;
    bool is_has_event;
    e_game_event game_event;
} t_menu_item_initializer;
typedef struct s_menu_item {
    char *text;
    SDL_Rect rect;
    SDL_Color color;
    SDL_Texture *texture;
    bool is_has_event;
    bool is_selected;
    e_game_event game_event;
} t_menu_item;

typedef struct s_menu {
    t_menu_item *items;
    int items_center_x;
    int items_center_y;
    int count;
    SDL_Rect rect;
    SDL_Texture *texture;
} t_menu;

typedef struct s_menu_manager {
    t_menu *start_menu;
    t_menu *pause_menu;
    t_menu *game_over_menu;
    t_menu *level_menu;
} t_menu_manager;

t_menu_item *init_menu_items(t_menu_item_initializer *items, SDL_Renderer *renderer, t_menu *menu);
void menu_draw_text(SDL_Renderer *renderer, char *text, SDL_Rect rect, SDL_Color color);
t_menu *menu_create(t_menu_item_initializer *items, int count, int x, int y, SDL_Renderer *renderer);
void menu_render(t_menu *menu, SDL_Renderer *renderer);
void menu_handle_event(t_menu *menu, SDL_Event *event);
void delete_menu_manager(t_menu_manager *menu_manager_ptr);
t_menu_manager get_menu_manager(SDL_Renderer *renderer);

#endif
