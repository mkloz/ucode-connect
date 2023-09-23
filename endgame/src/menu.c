#include "../inc/menu.h"

void menu_draw_text(SDL_Renderer *renderer, char *text, SDL_Rect rect, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(get_resources()->font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

static int calculate_y_pos(int center, int h, int i, int count) {
    return center - ((h + MENU_ITEM_PADDING) * count / 2) + i * (h + MENU_ITEM_PADDING);
}

t_menu_item *init_menu_items(t_menu_item_initializer *items, SDL_Renderer *renderer, t_menu *menu) {
    t_menu_item *it = (t_menu_item *) malloc(sizeof(t_menu_item) * menu->count);

    for (int i = 0; i < menu->count; i++) {
        it[i].is_selected = false;
        it[i].text = items[i].text;
        it[i].game_event = items[i].game_event;
        it[i].color = WHITE;
        it[i].is_has_event = items[i].is_has_event;

        SDL_Surface *surface = TTF_RenderText_Solid(get_resources()->font, items[i].text, it[i].color);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);

        it[i].texture = text;
        SDL_FreeSurface(surface);
        SDL_QueryTexture(it[i].texture, NULL, NULL,
                         &it[i].rect.w, &it[i].rect.h);
        it[i].rect.x = menu->items_center_x - it[i].rect.w / 2;
        it[i].rect.y = calculate_y_pos(menu->items_center_y, it[i].rect.h, i, menu->count);
    }

    return it;
}

t_menu *menu_create(t_menu_item_initializer *items, int count, int x, int y, SDL_Renderer *renderer) {
    t_menu *menu = (t_menu *) malloc(sizeof(t_menu));
    SDL_Rect rect = {x, y, WIDTH, HEIGHT};

    menu->texture = get_resources()->pause_menu;
    menu->count = count;
    menu->items_center_x = WIDTH / 2;
    menu->items_center_y = HEIGHT / 2;
    menu->rect = rect;
    menu->items = init_menu_items(items, renderer, menu);

    return menu;
}

void delete_menu_manager(t_menu_manager *menu_manager_ptr) {
    free(menu_manager_ptr->start_menu->items);
    free(menu_manager_ptr->start_menu);

    free(menu_manager_ptr->pause_menu->items);
    free(menu_manager_ptr->pause_menu);

    free(menu_manager_ptr->game_over_menu->items);
    free(menu_manager_ptr->game_over_menu);
}

void menu_render(t_menu *menu, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, menu->texture, NULL, &menu->rect);
    for (int i = 0; i < menu->count; i++) {
        t_menu_item item = menu->items[i];

        if (menu->items[i].is_has_event)
            item.color = menu->items[i].is_selected ? GREEN : WHITE;
        else
            item.color = GREEN;
        menu_draw_text(renderer, item.text, item.rect, item.color);
    }
}

void menu_handle_event(t_menu *p_menu, SDL_Event *event) {
    static SDL_Point mouse = {0, 0};
    switch (event->type) {
        case SDL_MOUSEMOTION:
            for (int i = 0; i < p_menu->count; ++i) {
                mouse.x = event->motion.x;
                mouse.y = event->motion.y;
                p_menu->items[i].is_selected = point_in_rect(mouse, p_menu->items[i].rect);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            for (int i = 0; i < p_menu->count; ++i) {
                if (point_in_rect(mouse, p_menu->items[i].rect)) {
                    p_menu->items[i].is_selected = true;
                    throw_user_event(p_menu->items[i].game_event);
                }
            }
            break;
    }
}

t_menu_manager get_menu_manager(SDL_Renderer *renderer) {
    t_menu_item_initializer start_items[] = {
            {"Start", true, GAME_EVENT_START},
            {"Quit",  true, GAME_EVENT_QUIT}};
    t_menu_item_initializer pause_items[] = {
            {"Continue", true, GAME_EVENT_CONTINUE},
            {"Restart",  true, GAME_EVENT_RESTART},
            {"Quit",     true, GAME_EVENT_QUIT}};
    t_menu_item_initializer game_over_items[] = {
            {"GAME OVER", false, -1},
            {"Restart",   true,  GAME_EVENT_RESTART},
            {"Quit",      true,  GAME_EVENT_QUIT}};
    t_menu_item_initializer levels[] = {
            {"Easy",   true, GAME_EVENT_LEVEL1},
            {"Normal", true, GAME_EVENT_LEVEL2},
            {"Hard",   true, GAME_EVENT_LEVEL3}};

    t_menu *pause_menu = menu_create(pause_items, 3, -20, -20, renderer);
    t_menu *start_menu = menu_create(start_items, 2, -20, -20, renderer);
    t_menu *game_over_menu = menu_create(game_over_items, 3, -20, -20, renderer);
    t_menu *level_menu = menu_create(levels, 3, -20, -20, renderer);

    t_menu_manager menu_manager = {start_menu, pause_menu, game_over_menu, level_menu};

    return menu_manager;
}
