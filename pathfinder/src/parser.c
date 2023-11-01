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

static long parse_first_line(char *line) {
    long cities_count = mx_atoi(line);

    if (cities_count <= 0
        || !is_numeric(line))
        mx_throw_invalid_line_err(1);

    return cities_count;
}

static void parse_line(t_graph *graph, char *line, int line_number) {

    int comma = mx_get_char_index(line, ',');
    int dash = mx_get_char_index(line, '-');

    if (comma <= 2
        || dash <= 0)
        mx_throw_invalid_line_err(line_number);

    long distance = mx_atoi(line + comma + 1);
    char *island1 = mx_strndup(line, dash);
    char *island2 = mx_strndup(line + dash + 1, comma - 1 - dash);

    if (distance <= 0 ||
		distance > MX_INT_MAX ||
        mx_strlen(island1) == 0 ||
        mx_strlen(island2) == 0 ||
        !is_alphabetical(island1) ||
        !is_alphabetical(island2) ||
        mx_strcmp(island1, island2) == 0||
        !is_numeric(line + comma + 1))
        mx_throw_invalid_line_err(line_number);

    mx_push_connection(graph, island1, island2, distance);
}

static char **get_lines(char *filename) {
    if (open(filename, O_RDONLY) < 0) {
        mx_throw_file_err(FILE_NOT_EXIST_ERR, filename);
        exit(EXIT_FAILURE);
    }

    char *file = mx_file_to_str(filename);
    if (file == NULL) mx_throw_file_err(FILE_IS_EMPTY_ERR, filename);

    char **res = mx_strsplit(file, '\n');
    mx_strdel(&file);

    return res;
}

static void handle_low_errors(t_graph *graph, long cities_count) {
    if (mx_list_size((t_list *) graph->stops) != cities_count)
        mx_throw_error(INVALID_ISLANDS_COUNT_ERR);

    long long sum = 0;

    for (t_connections_list *list = graph->connections; list != NULL; list = list->next) {
        mx_check_connection_uniqueness(&graph->connections, list->data);
        sum += list->data->distance;
    }

    if (sum > MX_INT_MAX) mx_throw_error(BRIDGES_SUM_TOO_BIG_ERR);
}

t_graph *mx_parse_file(char *name) {
    t_graph *graph = mx_create_graph();
    char **lines = get_lines(name);
    long cities_count = parse_first_line(lines[0]);

    for (int i = 1; lines[i] != NULL; i++) {
        parse_line(graph, lines[i], i + 1);
    }
    mx_del_strarr(&lines);
    handle_low_errors(graph, cities_count);

    return graph;
}
