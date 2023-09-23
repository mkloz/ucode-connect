#include "libmx.h"

int mx_atoi(const char *str) {
    int res = 0;
    int index = 0;
    int is_negative = false;

    while (mx_isspace(str[index])) {
        index++;
    }

    if (str[index] == '-') {
        is_negative = true;
        index++;
    }else if (str[index] == '+') {
        index++;
    }

    while (mx_isdigit(str[index])) {
        res = res * 10 + (str[index++] - '0');
    }

    return is_negative? res * -1 : res;
}
