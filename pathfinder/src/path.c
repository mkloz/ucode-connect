#include "path.h"
#include "graph.h"

t_city *mx_create_city(char *name, int distance) {
    t_city *city = malloc(sizeof(t_city));

    city->name = mx_strdup(name);
    city->distance = distance;
    return city;
}

t_routes_list *mx_create_routes(t_stop *previous) {
    t_routes_list *routes = NULL;

    if (previous->previous_stops == NULL) {
        t_list *route_start = NULL;
        mx_push_back(&route_start, mx_create_city(previous->name, previous->distance_from_start));
        mx_push_back((t_list **) &routes, route_start);
        return routes;
    }
    for (t_stops_list *stops_list = previous->previous_stops; stops_list != NULL; stops_list = stops_list->next) {
        t_routes_list *out = mx_create_routes(stops_list->data);

        for (t_routes_list *list = out; list != NULL; list = list->next) {
            t_city *city = mx_create_city(previous->name, previous->distance_from_start);
            mx_push_back((t_list **) &list->data, city);
        }
        mx_concat_lists((t_list **) &routes, (t_list **) &out);
    }

    return routes;
}

t_path *mx_create_path(t_stop *destination) {
    t_path *path = malloc(sizeof(t_path));

    path->routes = mx_create_routes(destination);
    path->from = mx_strdup(path->routes->data->data->name);
    path->to = mx_strdup(destination->name);

    return path;
}

void mx_delete_city(t_city *p_city) {
    mx_strdel(&p_city->name);
    free(p_city);
    p_city = NULL;
}

void mx_delete_route(t_route *p_route) {
    t_route *route = p_route;

    while (route) {
        mx_delete_city(route->data);
        mx_pop_front((t_list **) &route);
    }
    p_route = NULL;
}

void mx_delete_path(t_path *p_path) {
    mx_strdel(&p_path->to);
    mx_strdel(&p_path->from);
    for (t_routes_list *list = p_path->routes; list; list = list->next)
        mx_delete_route(list->data);
    free(p_path);
    p_path = NULL;
}
