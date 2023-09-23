#ifndef MKLOZ_ERRORS_H
#define MKLOZ_ERRORS_H

#include "base.h"

#define ERROR_USAGE "usage: ./pathfinder [filename]\n"
#define ERROR_DUPLICATED_BRIDGES "error: duplicate bridges\n"
#define ERROR_INVALID_ISLANDS_NUM "error: invalid number of islands\n"
#define ERROR_BRIDGES_SUM_TOO_BIG "error: sum of bridges lengths is too big\n"

enum error {
    USAGE_ERR,
    INVALID_ISLANDS_COUNT_ERR,
    DUPLICATED_BRIDGES_ERR,
    BRIDGES_SUM_TOO_BIG_ERR,
};

enum file_error {
    FILE_NOT_EXIST_ERR,
    FILE_IS_EMPTY_ERR,
};

void mx_throw_error(enum error error);
void mx_print_error(enum error error);
void mx_printerr(const char *s);
void mx_throw_file_err(enum file_error error, char *filename);
void mx_throw_invalid_line_err(int line);
#endif
