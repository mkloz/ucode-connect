#include "../inc/collider.h"

void collider_render(t_collider *collider_ptr, SDL_Renderer *rend_ptr) {
    if (IS_PRODUCTION) return;

    SDL_SetRenderDrawColor(rend_ptr, RED.r, RED.g, RED.b, RED.a);
    SDL_RenderDrawLine(rend_ptr, collider_ptr->p1.x, collider_ptr->p1.y, collider_ptr->p2.x, collider_ptr->p2.y);
    SDL_RenderDrawLine(rend_ptr, collider_ptr->p2.x, collider_ptr->p2.y, collider_ptr->p3.x, collider_ptr->p3.y);
    SDL_RenderDrawLine(rend_ptr, collider_ptr->p3.x, collider_ptr->p3.y, collider_ptr->p4.x, collider_ptr->p4.y);
    SDL_RenderDrawLine(rend_ptr, collider_ptr->p4.x, collider_ptr->p4.y, collider_ptr->p1.x, collider_ptr->p1.y);
}

void rotate_roint(SDL_Point *point, SDL_Point origin, double angle) {
    double rad = degrees_to_radians(angle);

    int x = (int) (cos(rad) * (point->x - origin.x) - sin(rad) * (point->y - origin.y) + origin.x);
    int y = (int) (sin(rad) * (point->x - origin.x) + cos(rad) * (point->y - origin.y) + origin.y);

    point->x = x;
    point->y = y;
}

void collider_init(t_collider *collider_ptr, SDL_Rect *rect, double angle) {
    SDL_Point origin = {(rect->x + (rect->w / 2)), rect->y + (rect->h / 2)};

    SDL_Point p1 = {rect->x, rect->y};
    rotate_roint(&p1, origin, angle);

    SDL_Point p2 = {rect->x + rect->w, rect->y};
    rotate_roint(&p2, origin, angle);

    SDL_Point p3 = {rect->x + rect->w, rect->y + rect->h};
    rotate_roint(&p3, origin, angle);

    SDL_Point p4 = {rect->x, rect->y + rect->h};
    rotate_roint(&p4, origin, angle);

    collider_ptr->p1 = p1;
    collider_ptr->p2 = p2;
    collider_ptr->p3 = p3;
    collider_ptr->p4 = p4;
}

t_collider empty_collider() {
    static SDL_Point p = {0, 0};
    t_collider collider = {p, p, p, p};

    return collider;
}

double area_of_triangle(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
    double side_a = distance_between(p1, p2);
    double side_b = distance_between(p2, p3);
    double side_c = distance_between(p3, p1);

    double semi_perimeter = (side_a + side_b + side_c) / 2.;

    double area = semi_perimeter * (semi_perimeter - side_a) * (semi_perimeter - side_b) * (semi_perimeter - side_c);

    return sqrt(area);
}

double area_of_collider(t_collider *collider_ptr) {
    double side_a = distance_between(collider_ptr->p1, collider_ptr->p2);
    double side_b = distance_between(collider_ptr->p1, collider_ptr->p4);

    return side_a * side_b;
}

bool collider_contains(t_collider *collider_ptr, SDL_Point *point_ptr) {
    double area1 = area_of_triangle(collider_ptr->p1, collider_ptr->p2, *point_ptr);
    double area2 = area_of_triangle(collider_ptr->p2, collider_ptr->p3, *point_ptr);
    double area3 = area_of_triangle(collider_ptr->p3, collider_ptr->p4, *point_ptr);
    double area4 = area_of_triangle(collider_ptr->p4, collider_ptr->p1, *point_ptr);

    double collider_area = area_of_collider(collider_ptr);
    double sum_area = area1 + area2 + area3 + area4;

    return sum_area <= collider_area;
}

bool collider_contact(t_collider *collider1_ptr, t_collider *collider2_ptr) {
    return collider_contains(collider1_ptr, &collider2_ptr->p1)
           || collider_contains(collider1_ptr, &collider2_ptr->p2)
           || collider_contains(collider1_ptr, &collider2_ptr->p3)
           || collider_contains(collider1_ptr, &collider2_ptr->p4);
}
