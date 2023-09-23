
#include "../inc/levels.h"

t_level_manager *get_level_manager_ptr() {
    static t_level_manager level_manager;
    return &level_manager;
}

void init_level_manager() {
    t_level_manager *level_manager = get_level_manager_ptr();

    level_manager->normal = NULL;
    level_manager->hard = NULL;
    level_manager->easy = NULL;
    level_manager->current = NULL;

    t_level_initializer easy_level = {
            EASY_START_ZOMBIE_COUNT,
            EASY_ZOMBIE_COUNT_INCREMENT,
            EASY_ZOMBIE_TIME_SPAWN,
            EASY_ZOMBIE_TIME_INCREMENT,
            EASY_MAX_ZOMBIE_COUNT,
            EASY_ZOMBIE_SPEED,
            EASY_SOLDIER_SPEED,
            get_resources()->background_texture1};
    t_level_initializer normal_level = {
            NORMAL_START_ZOMBIE_COUNT,
            NORMAL_ZOMBIE_COUNT_INCREMENT,
            NORMAL_ZOMBIE_TIME_SPAWN,
            NORMAL_ZOMBIE_TIME_INCREMENT,
            NORMAL_MAX_ZOMBIE_COUNT,
            NORMAL_ZOMBIE_SPEED,
            NORMAL_SOLDIER_SPEED,
            get_resources()->background_texture2};
    t_level_initializer hard_level = {
            HARD_START_ZOMBIE_COUNT,
            HARD_ZOMBIE_COUNT_INCREMENT,
            HARD_ZOMBIE_TIME_SPAWN,
            HARD_ZOMBIE_TIME_INCREMENT,
            HARD_MAX_ZOMBIE_COUNT,
            HARD_ZOMBIE_SPEED,
            HARD_SOLDIER_SPEED,
            get_resources()->background_texture3};

    level_manager->easy = create_level(
            easy_level);
    level_manager->normal = create_level(
            normal_level);
    level_manager->hard = create_level(
            hard_level);

    level_manager->current = level_manager->normal;
}

void destroy_level_manager() {
    t_level_manager *manager = get_level_manager_ptr();

    free(manager->easy);
    free(manager->normal);
    free(manager->hard);
}

t_level *create_level(t_level_initializer level_initializer) {
    t_level *level = malloc(sizeof(t_level));
    level->zombie_start_count = level_initializer.zombie_start_count;
    level->zombie_speed = level_initializer.zombie_speed;
    level->soldier_speed = level_initializer.soldier_speed;
    level->zombie_max_count = level_initializer.zombie_max_count;
    level->zombie_increment = level_initializer.zombie_increment;
    level->zombie_time_spawn = level_initializer.zombie_time_spawn;
    level->zombie_time_increment = level_initializer.zombie_time_increment;
    level->zombie_start_count = level_initializer.zombie_start_count;
    level->texture = level_initializer.texture;

    return level;
}

t_level *get_level_setting_ptr() {
    return get_level_manager_ptr()->current;
}

void set_level_setting(t_level *level) {
    get_level_manager_ptr()->current = level;
}

