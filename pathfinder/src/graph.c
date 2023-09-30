#include "graph.h"

t_graph *mx_create_graph(void) {
    t_graph *graph = (t_graph *) malloc(sizeof(t_graph));
    graph->stops = NULL;
    graph->connections = NULL;
    return graph;
}

t_stop *mx_init_empty_stop(char *name) {
    t_stop *stop = malloc(sizeof(t_stop));
    stop->name = name;
    stop->connections = NULL;
    stop->distance_from_start = MX_INT_MAX;
    stop->previous_stops = NULL;
    stop->is_visited = false;

    return stop;
}

t_stops_connection *mx_init_stops_connection(t_stop *first, t_stop *second, int distance) {
    t_stops_connection *conn = malloc(sizeof(t_stops_connection));
    conn->first = first;
    conn->second = second;
    conn->distance = distance;

    return conn;
}

t_stop *mx_push_stop_if_not_exist(t_stops_list **stops_list, char *name) {
    for (t_stops_list *stop = *stops_list; stop != NULL; stop = stop->next) {
        if (mx_strcmp(stop->data->name, name) == 0) {
            return stop->data;
        }
    }

    t_stop *new_stop = mx_init_empty_stop(name);
    mx_push_back((t_list **) stops_list, new_stop);

    return new_stop;
}

void mx_check_connection_uniqueness(t_connections_list **conn, t_stops_connection *current) {
    for (t_connections_list *conn_list = *conn; conn_list; conn_list = conn_list->next) {
        t_stop *f = conn_list->data->first;
        t_stop *s = conn_list->data->second;

        if (conn_list->data == current) continue;

        if (f == current->first
            || f == current->second) {
            if (s == current->first
                || s == current->second) {
                mx_throw_error(DUPLICATED_BRIDGES_ERR);
            }
        }
    }
}

void mx_push_connection(t_graph *graph, char *first, char *second, int distance) {
    if (!graph
        || !first
        || !second
        || !distance)
        return;
    t_stop *f_stop = mx_push_stop_if_not_exist(&graph->stops, first);
    t_stop *s_stop = mx_push_stop_if_not_exist(&graph->stops, second);
    t_stops_connection *conn = mx_init_stops_connection(
            f_stop, s_stop, distance);

    mx_push_back((t_list **) &f_stop->connections, conn);
    mx_push_back((t_list **) &s_stop->connections, conn);
    mx_push_back((t_list **) &graph->connections, conn);
}

