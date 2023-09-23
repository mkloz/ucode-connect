#ifndef MKLOZ_LIST_H
#define MKLOZ_LIST_H

typedef struct s_stop t_stop;
typedef struct s_city t_city;
typedef struct s_path t_path;
typedef struct s_stops_connection t_stops_connection;

typedef struct s_stops_list {
    t_stop *data;
    struct s_stops_list *next;
} t_stops_list;

typedef struct s_connections_list {
    t_stops_connection *data;
    struct s_connections_list *next;
} t_connections_list;

typedef struct s_route {
    t_city *data;
    struct s_route *next;
} t_route;

typedef struct s_routes_list {
    t_route *data;
    struct s_routes_list *next;
} t_routes_list;

typedef struct s_paths_list {
    t_path *data;
    struct s_paths_list *next;
} t_paths_list;

#endif
