#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    char *res = NULL;
    char *buf = mx_strnew(BUFSIZ);
    ssize_t n;
    int stream = open(filename, O_RDONLY);

    if (stream < 0)
        return NULL;

    while ((n = read(stream, buf, BUFSIZ)) > 0) {
        char *temp = mx_strjoin(res, buf);

        if (res != NULL)
            free(res);
        res = temp;
    }

    free(buf);

    if (n == -1)
        return NULL;
    if (close(stream) < 0) {

        return NULL;
    }

    return res;
}

