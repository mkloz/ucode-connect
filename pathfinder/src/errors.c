#include "errors.h"

void mx_printerr(const char *s) {
    write(STDERR_FILENO, s, mx_strlen(s));
}

static void file_not_exist_error(char *filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
}

static void file_is_empty_error(char *filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
}

void mx_print_error(enum error error) {
    switch (error) {
        case USAGE_ERR:
            mx_printerr(ERROR_USAGE);
            break;
        case INVALID_ISLANDS_COUNT_ERR:
            mx_printerr(ERROR_INVALID_ISLANDS_NUM);
            break;
        case DUPLICATED_BRIDGES_ERR:
            mx_printerr(ERROR_DUPLICATED_BRIDGES);
            break;
        case BRIDGES_SUM_TOO_BIG_ERR:
            mx_printerr(ERROR_BRIDGES_SUM_TOO_BIG);
            break;
        default: {
            mx_printerr("NOT_SUPPORTED_ERR\n");
        }
    }
}

void mx_throw_error(enum error error) {
    mx_print_error(error);

    exit(EXIT_FAILURE);
}

void mx_throw_file_err(enum file_error error, char *filename) {
    switch (error) {
        case FILE_NOT_EXIST_ERR:
            file_not_exist_error(filename);
            break;
        case FILE_IS_EMPTY_ERR:
            file_is_empty_error(filename);
            break;
        default: {
            mx_printerr("NOT_SUPPORTED_ERR\n");
        }
    }
    exit(EXIT_FAILURE);
}

void mx_throw_invalid_line_err(int line) {
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(line));
    mx_printerr(" is not valid\n");
    exit(EXIT_FAILURE);
}
