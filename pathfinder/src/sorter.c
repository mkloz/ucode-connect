#include "pathfinder.h"

static void swap_nodes(t_list *a, t_list *b) {
    if (a->data == b->data) return;

    void *temp = a->data;

    a->data = b->data;
    b->data = temp;
}

static int get_stop_index(t_stops_list *stops, const char *stop_name) {
    int index = 0;

    while (stops
           && mx_strcmp(stops->data->name, stop_name)) {
        index++;
        stops = stops->next;
    }

    return index;
}

static int get_stops_indexes_diff(t_stops_list *stops, char *stop_name, char *stop_2_name) {
    return get_stop_index(stops, stop_2_name) - get_stop_index(stops, stop_name);
}

static int compare_routes_by_stops(t_route *route1,
                                   t_route *route2,
                                   t_stops_list *stops) {
    if (!route1) {
        return route2 ? -1 : 0;
    } else if (!route2) {
        return 1;
    }

    while (route1 && route2) {
        int order = get_stops_indexes_diff(stops, route1->data->name, route2->data->name);

        if (order != 0) {
            return order;
        }

        route1 = route1->next;
        route2 = route2->next;
    }

    return 0;
}

static int compare_paths_by_stops(t_path *path1,
                                  t_path *path2,
                                  t_stops_list *stops) {
    if (!path1) {
        return path2 ? -1 : 0;
    } else if (!path2) {
        return 1;
    }

    int from_diff = get_stops_indexes_diff(stops, path1->from, path2->from);
    int to_diff = get_stops_indexes_diff(stops, path1->to, path2->to);

    return from_diff == 0 ? to_diff : from_diff;
}

static void sort_routes_in_path(t_path *path, t_stops_list *stops) {
    for (t_routes_list *index = path->routes; index; index = index->next) {
        t_routes_list *biggest = index;

        for (t_routes_list *current = index->next; current; current = current->next) {
            if (compare_routes_by_stops(biggest->data, current->data, stops) < 0) {
                biggest = current;
            }
        }
        if (biggest != index) {
            swap_nodes((t_list *) biggest, (t_list *) index);
        }
    }
}

void mx_sort_paths_in_stops_order(t_paths_list *paths, t_stops_list *stops) {
    for (t_paths_list *index = paths; index; index = index->next) {
        t_paths_list *biggest = index;

        for (t_paths_list *current = index->next; current; current = current->next) {
            if (compare_paths_by_stops(biggest->data, current->data, stops) < 0) {
                biggest = current;
            }
        }
        if (biggest != index) {
            swap_nodes((t_list *) biggest, (t_list *) index);
        }
        sort_routes_in_path(index->data, stops);
    }
}

