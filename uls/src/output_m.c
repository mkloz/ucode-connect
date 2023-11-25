#include "uls.h"

static void printn(int *len) {
    (*len) = 0;
    mx_printchar('\n');
}

static void print_names(t_element **names, int wincol, t_flags *fl) {
    int len = 0;
    int nextlen = 0;

    for (int i = 0; names[i]; i++) {
        if (fl->G)
            mx_printstr_g(names[i]);
        else if (!fl->G)
            mx_printstr(names[i]->name);
        len += mx_strlen(names[i]->name) + 2;
        if (names[i + 1]) {
            mx_printstr(", ");
            if (names[i + 2])
                nextlen = 3;
            else
                nextlen = 1;
            if (len + nextlen + mx_strlen(names[i + 1]->name) > wincol)
                printn(&len);
        }
    }
    mx_printchar('\n');
}

void mx_output_m(t_element **names, t_flags *fl) {
    struct winsize win;

    if (!names)
        return;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(STDOUT_FILENO))
        print_names(names, win.ws_col, fl);
    else
        print_names(names, 80, fl);
}
