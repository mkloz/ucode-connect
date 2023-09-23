#ifndef MYEZIK_COMMON_H
#define MYEZIK_COMMON_H

#include <stdio.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <stdbool.h>
#include <math.h>
#include "list.h"
#include "SDL2/SDL_mixer.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#undef main
#define EXIT_FAILURE 1

#define HEIGHT 800
#define WIDTH 800

#define IS_PRODUCTION 1

static const SDL_Color WHITE = {255, 255, 255, 255};
static const SDL_Color YELLOW = {217, 173, 28, 255};
static const SDL_Color RED = {255, 0, 0, 255};
static const SDL_Color GREEN = {60, 150, 38, 255};

typedef enum {
    GAME_EVENT_START,
    GAME_EVENT_SOLDIER_DEAD,
    GAME_EVENT_PAUSE,
    GAME_EVENT_QUIT,
    GAME_EVENT_CONTINUE,
    GAME_EVENT_RESTART,
    GAME_EVENT_CHOOSE_LEVEL,
    GAME_EVENT_LEVEL1,
    GAME_EVENT_LEVEL2,
    GAME_EVENT_LEVEL3,
} e_game_event;

typedef enum {
    GAME_STATE_PLAYING,
    GAME_STATE_START,
    GAME_STATE_PAUSE,
    GAME_STATE_QUIT,
    GAME_STATE_RESTARTING,
    GAME_STATE_AFTER_DEATH,
    GAME_STATE_LEVEL_CHOOSING,
} e_game_state;

e_game_state *get_game_state_ptr();
e_game_state get_game_state();
void set_game_state(e_game_state game_state);
SDL_Texture *load_texture_from_file(const char *path_to_file, SDL_Renderer *renderer);
double angle_of(SDL_Point p1, SDL_Point p2);
double radians_to_degrees(double radian);
double degrees_to_radians(double degree);
double get_random_num(int min, int max);
bool point_in_rect(SDL_Point point, SDL_Rect rect);
double distance_between(SDL_Point p1, SDL_Point p2);
int get_offset_x(double speed, double angle);
int get_offset_y(double speed, double angle);
void throw_user_event(int code);
#endif
