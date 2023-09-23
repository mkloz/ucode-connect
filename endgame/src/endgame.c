#include "../inc/endgame.h"

void handle_event(SDL_Event *event) {
    switch (event->type) {
        case SDL_QUIT:
            set_game_state(GAME_STATE_QUIT);
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_p) {
                if (get_game_state() == GAME_STATE_PAUSE)
                    set_game_state(GAME_STATE_PLAYING);
                else if (get_game_state() == GAME_STATE_PLAYING)
                    set_game_state(GAME_STATE_PAUSE);
            }
            break;
        case SDL_USEREVENT: {
            e_game_event game_event = event->user.code;
            t_level_manager *manager = get_level_manager_ptr();

            switch (game_event) {
                case GAME_EVENT_START:
                    set_game_state(GAME_STATE_LEVEL_CHOOSING);
                    break;
                case GAME_EVENT_SOLDIER_DEAD:
                    set_game_state(GAME_STATE_AFTER_DEATH);
                    break;
                case GAME_EVENT_RESTART:
                    set_game_state(GAME_STATE_RESTARTING);
                    break;
                case GAME_EVENT_QUIT:
                    set_game_state(GAME_STATE_QUIT);
                    break;
                case GAME_EVENT_PAUSE:
                    set_game_state(GAME_STATE_PAUSE);
                    break;
                case GAME_EVENT_CONTINUE:
                    set_game_state(GAME_STATE_PLAYING);
                    break;
                case GAME_EVENT_LEVEL1:
                    set_level_setting(manager->easy);
                    set_game_state(GAME_STATE_PLAYING);
                    break;
                case GAME_EVENT_LEVEL2:
                    set_level_setting(manager->normal);
                    set_game_state(GAME_STATE_PLAYING);
                    break;
                case GAME_EVENT_LEVEL3:
                    set_level_setting(manager->hard);
                    set_game_state(GAME_STATE_PLAYING);
                    break;
                default:
                    break;
            }
        }
        default:
            break;
    }
}

Uint32 spawn_zombie(Uint32 interval, t_zombie_list *zombie_list) {
    if (get_game_state() != GAME_STATE_PLAYING)
        return interval;

    for (int i = zombie_list->list_size; i < zombie_list->zombie_count; ++i)
        mx_push_back((t_list **) &zombie_list->list, zombie_generate());

    zombie_list->list_size = zombie_list->zombie_count;

    return interval;
}

Uint32 increment_zombie_count(Uint32 interval, t_zombie_list *zombie_list) {
    t_level *level = get_level_setting_ptr();
    if (get_game_state() != GAME_STATE_PLAYING)
        return interval;

    if ((zombie_list->zombie_count + level->zombie_increment) < level->zombie_max_count)
        zombie_list->zombie_count += level->zombie_increment;

    return interval;
}

void one_game(SDL_Renderer *renderer) {
    t_level *l_settings = get_level_setting_ptr();
    t_soldier soldier;
    soldier_init(&soldier);

    SDL_Event event;
    t_zombie_list zombie_list = {NULL, 0, l_settings->zombie_start_count};
    t_menu_manager menu_manager = get_menu_manager(renderer);
    t_button button;
    button_init(&button);

    SDL_TimerID zombie_spawn_timer = SDL_AddTimer(
            l_settings->zombie_time_spawn,
            (SDL_TimerCallback) spawn_zombie, &zombie_list);
    SDL_TimerID zombie_increment_timer = SDL_AddTimer(
            l_settings->zombie_time_increment,
            (SDL_TimerCallback) increment_zombie_count, &zombie_list);

    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            e_game_state game_state = get_game_state();

            switch (game_state) {
                case GAME_STATE_START:
                    menu_handle_event(menu_manager.start_menu, &event);
                    break;
                case GAME_STATE_AFTER_DEATH:
                    menu_handle_event(menu_manager.game_over_menu, &event);
                    break;
                case GAME_STATE_PAUSE:
                    menu_handle_event(menu_manager.pause_menu, &event);
                    break;
                case GAME_STATE_LEVEL_CHOOSING:
                    menu_handle_event(menu_manager.level_menu, &event);
                    break;
                case GAME_STATE_PLAYING:
                    button_handle_event(&button, &event);
                    soldier_handle_event(&soldier, &event);
                    break;
                default:
                    break;
            }

            handle_event(&event);
        }
        l_settings = get_level_setting_ptr();

        switch (get_game_state()) {
            case GAME_STATE_PLAYING: {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, l_settings->texture, NULL, NULL);

                soldier_render(&soldier, renderer);
                soldier_handle_tick(&soldier, &zombie_list);

                for (t_list *temp = zombie_list.list; temp != NULL; temp = temp->next) {
                    zombie_render((t_zombie *) temp->data, renderer);
                    zombie_handle_tick((t_zombie *) temp->data, &soldier);
                }

                button_render(&button, renderer);
                draw_counter(soldier.kills, renderer);

                mx_del_node_if(&soldier.bullets, (bool (*)(void *)) bullet_is_invalid);
                mx_del_node_if(&zombie_list.list, (bool (*)(void *)) zombie_is_dead);
                break;
            }
            case GAME_STATE_PAUSE:
                menu_render(menu_manager.pause_menu, renderer);
                break;
            case GAME_STATE_START:
                menu_render(menu_manager.start_menu, renderer);
                break;
            case GAME_STATE_QUIT:
                quit = true;
                break;
            case GAME_STATE_RESTARTING:
                quit = true;
                set_game_state(GAME_STATE_LEVEL_CHOOSING);
                break;
            case GAME_STATE_AFTER_DEATH:
                menu_render(menu_manager.game_over_menu, renderer);
                break;
            case GAME_STATE_LEVEL_CHOOSING:
                menu_render(menu_manager.level_menu, renderer);
                break;
            default:
                break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }

    SDL_RemoveTimer(zombie_spawn_timer);
    SDL_RemoveTimer(zombie_increment_timer);

    delete_menu_manager(&menu_manager);
    mx_clear_list(&zombie_list.list);
    mx_clear_list(&soldier.bullets);
}

void endgame() {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0 || TTF_Init() != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0) {
        fprintf(stderr, "Could not create window or renderer%s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) < 0) {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    if (Mix_AllocateChannels(64) < 0) {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        exit(-1);
    }

    resources_init(renderer);
    init_level_manager();
    set_level_setting(get_level_manager_ptr()->normal);

    while (get_game_state() != GAME_STATE_QUIT)
        one_game(renderer);

    resources_destroy();
    destroy_level_manager();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
