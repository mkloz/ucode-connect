#include "pathfinder.h"

int main(int argc, char **argv) {
    if (argc != 2) mx_throw_error(USAGE_ERR);

    t_graph *graph = mx_parse_file(argv[1]);
    t_paths_list *paths_list = mx_find_all_routes(graph);

    mx_sort_paths_in_fifo_order(paths_list, graph->stops);
    mx_print_paths(paths_list);

    return 0;
}
