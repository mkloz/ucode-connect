int mx_strlen(const char *s);
char *mx_strcpy(char *dst, const char *src);
char *mx_strnew(const int size);

char *mx_strdup(const char *str) {
    char *c = mx_strnew(mx_strlen(str));

    mx_strcpy(c, str);

    return c;
}

