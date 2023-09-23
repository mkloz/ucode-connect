#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    if (dst == NULL) return NULL;
    char *ptr = dst;

    while (*src && len--) {
        *dst = *src;
        dst++;
        src++;
    }

    *dst = '\0';
    return ptr;
}
