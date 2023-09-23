#include "pathfinder.h"

static void swap_paths(t_paths_list *a, t_paths_list *b) {
    t_path *temp = a->data;
    a->data = b->data;
    b->data = temp;
}

static int get_stop_index(t_stops_list *stops, const char *stop_name) {
    int index = 0;
    t_stops_list *current_stop = stops;

    while (current_stop != NULL && mx_strcmp(current_stop->data->name, stop_name) != 0) {
        index++;
        current_stop = current_stop->next;
    }

    return index;
}

static int compare_stops_order(t_stops_list *stops, char *stop1, char *stop2) {
    // Compare the order of two stops in the stops list
    int index1 = get_stop_index(stops, stop1);
    int index2 = get_stop_index(stops, stop2);

    if (index1 < index2) {
        return -1;
    } else if (index1 > index2) {
        return 1;
    }

    return 0;
}

static int compare_routes_by_stops(t_routes_list *route1, t_routes_list *route2, t_stops_list *stops) {
    t_route *stops1 = route1->data;
    t_route *stops2 = route2->data;

    while (stops1 != NULL && stops2 != NULL) {
        int order = compare_stops_order(stops, stops1->data->name, stops2->data->name);

        if (order != 0) {
            return order;
        }

        stops1 = stops1->next;
        stops2 = stops2->next;
    }

    if (stops1 == NULL && stops2 != NULL) {
        return -1;
    } else if (stops1 != NULL && stops2 == NULL) {
        return 1;
    }

    return 0;
}

static void insert_sorted_route(t_routes_list **sorted_routes, t_routes_list *current_route, t_stops_list *stops) {
    t_routes_list *prev = NULL;
    t_routes_list *current = *sorted_routes;

    while (current != NULL && compare_routes_by_stops(current_route, current, stops) > 0) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        current_route->next = *sorted_routes;
        *sorted_routes = current_route;
    } else {
        prev->next = current_route;
        current_route->next = current;
    }
}

static void sort_routes_in_path(t_path *path, t_stops_list *stops) {
    t_routes_list *sorted_routes = NULL;

    while (path->routes != NULL) {
        t_routes_list *current_route = path->routes;
        path->routes = path->routes->next;

        insert_sorted_route(&sorted_routes, current_route, stops);
    }

    path->routes = sorted_routes;
}

void mx_sort_paths_in_fifo_order(t_paths_list *paths, t_stops_list *stops) {
    for (t_paths_list *current_path = paths; current_path != NULL; current_path = current_path->next) {
        sort_routes_in_path(current_path->data, stops);

        t_paths_list *temp = current_path;
        int current_from_index = get_stop_index(stops, current_path->data->from);
        int current_to_index = get_stop_index(stops, current_path->data->to);

        while (temp->next != NULL) {
            int next_from_index = get_stop_index(stops, temp->next->data->from);
            int next_to_index = get_stop_index(stops, temp->next->data->to);

            if (next_from_index < current_from_index ||
                (next_from_index == current_from_index && next_to_index < current_to_index)) {
                swap_paths(temp, temp->next);
                current_from_index = next_from_index;
                current_to_index = next_to_index;
            }

            temp = temp->next;
        }
    }
}

