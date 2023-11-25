#include "uls.h"

void mx_output_err(t_element ***error, t_flags *fl) {
    if (error && *error && **error) {
	    mx_sort_elements(error, fl);
        fl->files = true;
        fl->ex = true;
        for (int i = 0; (*error)[i]; i++) {
            mx_printerr("uls: ");
            mx_printerr((*error)[i]->name);
            mx_printerr(": ");
            mx_printerr((*error)[i]->error_message);
            mx_printerr("\n");
            mx_strdel(&(*error)[i]->name);
            mx_strdel(&(*error)[i]->path);
            mx_strdel(&(*error)[i]->error_message);
            free((*error)[i]);
            (*error)[i] = NULL;
        }
        free(*error);
        *error = NULL;
    }
}

void mx_printchar_err(char c) {
    write(STDERR_FILENO,&c,1);
}
