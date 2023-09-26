#ifndef MKLOZ_PATHFINDER_H
#define MKLOZ_PATHFINDER_H

#include "libmx.h"
#include "graph.h"
#include "path.h"
#include "helpers.h"
#include "errors.h"

#define BOUNDARY_SIZE 40

void mx_print_path(t_path *path);
void mx_print_paths(t_paths_list *paths);
t_graph *mx_parse_file(char *name);
void mx_sort_paths_in_stops_order(t_paths_list *paths, t_stops_list *stops);
t_paths_list *mx_find_all_routes(t_graph *graph);
#endif
