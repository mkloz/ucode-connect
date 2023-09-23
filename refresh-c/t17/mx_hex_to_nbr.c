#include <stdbool.h>

static bool isalpha(char c) {
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

static bool isdigit(int c) {
    return c >= 48 && c <= 57;
}

static bool islower(int c) {
    return c >= 97 && c <= 122;
}

static bool isupper(int c) {
    return c >= 65 && c <= 90;
}

static int get_len(const char *hex) {
    int i = 0;

    while (hex[i] != '\0') {
        i++;
    }

    return i;
}

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long temp = 1;
    unsigned long res = 0;
    int len = get_len(hex);

    for (int i = len - 1; i >= 0; --i) {
        char ch = hex[i];

        if (isalpha(ch)) {
            res += (ch - (islower(ch) ? 87 : 55)) * temp;
        } else if (isdigit(ch)) {
            res += (ch - 48) * temp;
        } else if (isupper(ch)) {
            return 0;
        }

        temp *= 16;
    }

    return res;
}
