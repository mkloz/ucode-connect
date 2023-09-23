#include "libmx.h"

static char *split_word(const char *start, const char *end) {
    int len = end - start;
    char *word = mx_strndup(start, len);
    return word;
}

char **mx_strsplit(const char *s, char c) {
    if (!s) {
        return NULL;
    }

    int word_count = mx_count_words(s, c);
    char **arr = (char **)malloc(sizeof(char *) * (word_count + 1));
    int i = 0;

    while (*s != '\0') {
        if (*s != c) {
            const char *word_start = s;

            while (*s != '\0' && *s != c) {
                s++;
            }
            arr[i] = split_word(word_start, s);

            i++;
        } else {
            s++;
        }
    }

    arr[i] = NULL;

    return arr;
}
