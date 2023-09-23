#include "pathfinder.h"

static void print_path(char *from, char *to) {
    mx_printstr("Path: ");
    mx_printstr(from);
    mx_printstr(" -> ");
    mx_printstr(to);
    mx_printchar('\n');
}

static void print_route(t_route *route_list) {
    mx_printstr("Route: ");

    for (t_route *route = route_list; route != NULL; route = route->next) {
        if (route->next) {
            mx_printstr(route->data->name);
            mx_printstr(" -> ");
            continue;
        }

        mx_printstr(route->data->name);
    }

    mx_printchar('\n');
}

static void print_boundary(void) {
    for (int i = 0; i < BOUNDARY_SIZE; i++) {
        mx_printchar('=');
    }

    mx_printchar('\n');
}

static void print_distance(t_route *current) {
    mx_printstr("Distance: ");
    int prev_distance = 0;

    for (t_route *route = current->next; route != NULL; route = route->next) {
        int distance = route->data->distance - prev_distance;

        if (route->next != NULL) {
            mx_printint(distance);
            mx_printstr(" + ");
            prev_distance = route->data->distance;
            continue;
        }
        if (route != current->next) {
            mx_printint(distance);
            mx_printstr(" = ");
        }
        mx_printint(route->data->distance);
    }
    mx_printchar('\n');
}

void mx_print_path(t_path *path) {
    for (t_routes_list *route = path->routes; route != NULL; route = route->next) {
        print_boundary();
        print_path(path->from, path->to);
        print_route(route->data);
        print_distance(route->data);
        print_boundary();
    }
}

void mx_print_paths(t_paths_list *paths) {
    for (t_paths_list *routes = paths; routes != NULL; routes = routes->next) {
        mx_print_path(routes->data);
    }
}

