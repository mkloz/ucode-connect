#ifndef MKLOZ_PATH_H
#define MKLOZ_PATH_H

#include "base.h"

typedef struct s_stop t_stop;

typedef struct s_city {
    char *name;
    int distance;
} t_city;

typedef struct s_path {
    t_routes_list *routes;
    char *from;
    char *to;
} t_path;

t_city *mx_create_city(char *name, int distance);
t_routes_list *mx_create_routes(t_stop *previous);
t_path *mx_create_path(t_stop *destination);
void mx_delete_city(t_city *p_city);
void mx_delete_route(t_route *p_route);
void mx_delete_path(t_path *p_path);

#endif //MKLOZ_PATH_H
