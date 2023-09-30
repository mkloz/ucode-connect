#include "pathfinder.h"

static bool is_paths_equal(t_path *data, t_path *expected) {
    bool res = ((mx_strcmp(data->to, expected->to) == 0
                 || mx_strcmp(data->to, expected->from) == 0) &&
                (mx_strcmp(data->from, expected->to) == 0
                 || mx_strcmp(data->from, expected->from) == 0));
    return res;
}

static void add_current_to_paths_list(t_paths_list **routes_list, t_stop *destination) {
    if (destination->previous_stops == NULL) {
        return;
    }
    t_path *path = mx_create_path(destination);
    t_paths_list *route = (t_paths_list *) mx_list_find_where((t_list *) *routes_list, path,
                                                              (t_comp_func *) is_paths_equal);

    if (!route) {
        mx_push_back((t_list **) routes_list, path);
        return;
    }
    mx_delete_path(path);
}

static void add_neighbors_to_queue(t_stops_list **queue, t_stop *current) {
    for (t_connections_list *conn = (*queue)->data->connections; conn != NULL; conn = conn->next) {
        t_stop *neighbor = conn->data->first != current ? conn->data->first : conn->data->second;
        if (neighbor->is_visited) continue;

        int distance =
                current->distance_from_start == MX_INT_MAX ?
                MX_INT_MAX : current->distance_from_start + conn->data->distance;

        if (neighbor->distance_from_start > distance) {
            neighbor->distance_from_start = distance;
            mx_clear_list((t_list **) &neighbor->previous_stops);
            mx_push_back((t_list **) &neighbor->previous_stops, current);
        } else if (neighbor->distance_from_start == distance) {
            mx_push_back((t_list **) &neighbor->previous_stops, current);
        }
        mx_push_back((t_list **) queue, neighbor);
    }

    current->is_visited = true;
}

static bool compare_stops_by_distance(t_stop stop1, t_stop stop2) {
    return stop1.distance_from_start > stop2.distance_from_start;
}

static void search_routes(t_paths_list **routes_list, t_stops_list *start) {
    t_stops_list *queue = NULL;

    mx_push_back((t_list **) &queue, start->data);

    while (queue) {
        mx_sort_list((t_list *) queue, (t_comp_func *) compare_stops_by_distance);
        if (!queue->data->is_visited) {
            add_neighbors_to_queue(&queue, queue->data);
            add_current_to_paths_list(routes_list, queue->data);
        }

        mx_pop_front((t_list **) &queue);
    }
}

t_paths_list *mx_find_all_routes(t_graph *graph) {
    t_paths_list *routes_list = NULL;

    for (t_stops_list *el = graph->stops; el != NULL; el = el->next) {
        for (t_stops_list *p_list = graph->stops;
             p_list != NULL; p_list = p_list->next) {
            p_list->data->distance_from_start = MX_INT_MAX;
            mx_clear_list((t_list **) &p_list->data->previous_stops);
            p_list->data->is_visited = false;
        }
        el->data->distance_from_start = 0;
        el->data->previous_stops = NULL;

        search_routes(&routes_list, el);
    }

    return routes_list;
}

