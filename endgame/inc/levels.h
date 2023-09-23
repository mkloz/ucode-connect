#ifndef MYEZIK_LEVELS_H
#define MYEZIK_LEVELS_H

#define EASY_START_ZOMBIE_COUNT 3
#define EASY_ZOMBIE_COUNT_INCREMENT 1
#define EASY_ZOMBIE_TIME_SPAWN 3000
#define EASY_ZOMBIE_TIME_INCREMENT 15000
#define EASY_MAX_ZOMBIE_COUNT 10
#define EASY_ZOMBIE_SPEED 1.6
#define EASY_SOLDIER_SPEED 3

#define NORMAL_START_ZOMBIE_COUNT 5
#define NORMAL_ZOMBIE_COUNT_INCREMENT 1
#define NORMAL_ZOMBIE_TIME_SPAWN 2000
#define NORMAL_ZOMBIE_TIME_INCREMENT 12500
#define NORMAL_MAX_ZOMBIE_COUNT 14
#define NORMAL_ZOMBIE_SPEED 2
#define NORMAL_SOLDIER_SPEED 4

#define HARD_START_ZOMBIE_COUNT 3
#define HARD_ZOMBIE_COUNT_INCREMENT 2
#define HARD_ZOMBIE_TIME_SPAWN 1500
#define HARD_ZOMBIE_TIME_INCREMENT 10000
#define HARD_MAX_ZOMBIE_COUNT 16
#define HARD_ZOMBIE_SPEED 2.2
#define HARD_SOLDIER_SPEED 5

#include "common.h"
#include "resourses.h"

typedef struct s_level_initializer {
    int zombie_start_count;
    int zombie_increment;
    int zombie_time_spawn;
    int zombie_time_increment;
    int zombie_max_count;
    double zombie_speed;
    double soldier_speed;
    SDL_Texture *texture;
} t_level_initializer;

typedef struct s_level {
    int zombie_start_count;
    int zombie_increment;
    int zombie_time_spawn;
    int zombie_time_increment;
    int zombie_max_count;
    double zombie_speed;
    double soldier_speed;
    SDL_Texture *texture;
} t_level;

typedef struct s_level_manager {
    t_level *easy;
    t_level *normal;
    t_level *hard;

    t_level *current;
} t_level_manager;

void init_level_manager();
void destroy_level_manager();
t_level_manager *get_level_manager_ptr();
t_level *create_level(t_level_initializer level_initializer);
t_level *get_level_setting_ptr();
void set_level_setting(t_level *level);
#endif
