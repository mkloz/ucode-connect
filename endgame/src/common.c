#include "../inc/common.h"

double radians_to_degrees(double radian) {
    return (radian) * (180 / M_PI);
}

double degrees_to_radians(double degree) {
    if (degree < 0)
        degree = 360 + degree;
    else if (degree > 360)
        degree = degree - 360;

    return (degree) * (M_PI / 180.0);
}

double distance_between(SDL_Point p1, SDL_Point p2) {
    return sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

SDL_Texture *load_texture_from_file(const char *path_to_file, SDL_Renderer *renderer) {
    SDL_Texture *pTexture = IMG_LoadTexture(renderer, path_to_file);

    if (!pTexture) {
        fprintf(stderr, "Error while loading texture %s\n", path_to_file);
        exit(EXIT_FAILURE);
    }

    return pTexture;
}

double get_random_num(int min, int max) {
    return min + ((rand() / (RAND_MAX + 0.0)) * max);
}

void throw_user_event(int code) {
    SDL_Event user_event;

    user_event.type = SDL_USEREVENT;
    user_event.user.code = code;
    user_event.user.data1 = NULL;
    user_event.user.data2 = NULL;
    SDL_PushEvent(&user_event);
}

int get_offset_x(double speed, double angle) {
    return cos(degrees_to_radians(angle)) * speed;
}

int get_offset_y(double speed, double angle) {
    return sin(degrees_to_radians(angle)) * speed;
}

double angle_of(SDL_Point p1, SDL_Point p2) {
    double deltaY = (p2.y - p1.y);
    double deltaX = (p2.x - p1.x);

    double theta = atan2(deltaY, deltaX);
    if (theta < 0.0)
        theta += M_PI * 2;
    return radians_to_degrees(theta);
}

bool point_in_rect(SDL_Point point, SDL_Rect rect) {
    return point.x >= rect.x
           && point.x <= rect.x + rect.w
           && point.y >= rect.y
           && point.y <= rect.y + rect.h;
}

e_game_state *get_game_state_ptr() {
    static e_game_state game_state = GAME_STATE_START;
    return &game_state;
}

e_game_state get_game_state() {
    return *get_game_state_ptr();
}

void set_game_state(e_game_state game_state) {
    *get_game_state_ptr() = game_state;
}
