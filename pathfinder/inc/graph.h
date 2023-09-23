#ifndef GRAPH_H
#define GRAPH_H

#include "helpers.h"
#include "base.h"

typedef struct s_stops_connection t_stops_connection;
typedef struct s_graph t_graph;
typedef struct s_stop t_stop;

struct s_stops_connection {
    t_stop *first;
    int distance;
    t_stop *second;
};

struct s_graph {
    t_stops_list *stops;
    t_connections_list *connections;
};

struct s_stop {
    char *name;
    t_stops_list *previous_stops;
    int distance_from_start;
    bool is_visited;
    t_connections_list *connections;
};

t_graph *mx_create_graph(void);
t_stops_connection *mx_init_stops_connection(t_stop *first, t_stop *second, int distance);
void mx_push_connection(t_graph *graph, char *first, char *second, int distance);
void mx_check_connection_uniqueness(t_connections_list **conn, t_stops_connection *connection);
t_stop *mx_init_empty_stop(char *name);
#endif
