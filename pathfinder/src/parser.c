#include "pathfinder.h"

static bool is_alphabetical(const char *line) {
    while (*line != '\0') {
        if (!mx_isalpha(*line)) {
            return false;
        }
        line++;
    }
    return true;
}

static bool is_numeric(const char *line) {
    while (*line != '\0') {
        if (!mx_isdigit(*line)) {
            return false;
        }
        line++;
    }
    return true;
}

static void parse_line(t_graph *graph, char *line, int line_number) {
    int comma = mx_get_char_index(line, ',');
    int dash = mx_get_char_index(line, '-');

    if (comma <= 2
        || dash <= 0)
        mx_throw_invalid_line_err(line_number);

    int distance = mx_atoi(line + comma + 1);
    char *island1 = mx_strndup(line, dash);
    char *island2 = mx_strndup(line + dash + 1, comma - 1 - dash);

    if (distance <= 0 ||
        mx_strlen(island1) == 0 ||
        mx_strlen(island2) == 0 ||
        !is_alphabetical(island1) ||
        !is_alphabetical(island2) ||
        mx_strcmp(island1, island2) == 0)
        mx_throw_invalid_line_err(line_number);

    mx_push_connection(graph, island1, island2, distance);
}

t_graph *mx_parse_file(char *name) {
    t_graph *graph = mx_create_graph();
    char *str = NULL;
    int line_number = 1;
    int fd = open(name, O_RDONLY);

    if (fd < 0) mx_throw_file_err(FILE_NOT_EXIST_ERR, name);

    int readed = mx_read_line(&str, 1, '\n', fd);

    if (readed == -1) mx_throw_file_err(FILE_IS_EMPTY_ERR, name);

    int cities_count = mx_atoi(str);

    if (cities_count <= 0
        || !is_numeric(str))
        mx_throw_invalid_line_err(line_number);
    mx_strdel(&str);

    while (mx_read_line(&str, 1, '\n', fd) >= 0) {
        line_number++;
        parse_line(graph, str, line_number);
        mx_strdel(&str);
    }
    if (mx_list_size((t_list *) graph->stops) != cities_count)
        mx_throw_error(INVALID_ISLANDS_COUNT_ERR);

    long long sum = 0;

    for (t_connections_list *list = graph->connections; list != NULL; list = list->next) {
        mx_check_connection_uniqueness(&graph->connections, list->data);
        sum += list->data->distance;
    }

    if (sum > INT_MAX) mx_throw_error(BRIDGES_SUM_TOO_BIG_ERR);
    return graph;
}
