#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int c = 0;
    char *found = NULL;

    while ((found = mx_strstr(str, sub)) != NULL) {
        str = found + mx_strlen(sub);
        c++;
    }

    return c;
}

