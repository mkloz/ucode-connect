#include "uls.h"

static void output_1(t_element **names, t_flags *fl) {
	for (int i = 0; names[i]; i++) {
		if (!fl->G)
			mx_printstr(names[i]->name);
		else
			mx_printstr_g(names[i]);
		mx_printchar('\n');
	}
}

void mx_del_arr_arr(t_element ***args) {
	t_element **del_arr = *args;

	for (int i = 0; del_arr[i] != NULL; i++) {
		mx_strdel(&del_arr[i]->name);
		mx_strdel(&del_arr[i]->path);
		if (del_arr[i]->error_message)
			mx_strdel(&del_arr[i]->error_message);
		if (del_arr[i]->inner_elements != NULL)
			mx_del_arr_arr(&del_arr[i]->inner_elements);
		free(del_arr[i]);
		del_arr[i] = NULL;
	}
	free(*args);
	*args = NULL;
}

void mx_output(t_element ***names, t_flags *fl, int flag) {
	if (**names != NULL) {
		mx_sort_elements(&(*names), fl);

		if (fl->long_out)
			mx_output_l(*names, fl, flag);
		if (fl->C && !fl->G)
			mx_output_c(*names);
		if (fl->x && !fl->G)
			mx_output_x(*names);
		if (fl->m)
			mx_output_m(*names, fl);
		if (fl->force)
			output_1(*names, fl);
		if (fl->G && !fl->m && !fl->long_out && !fl->force)
			mx_output_g(*names, fl);
		if (!fl->long_out && !fl->C && !fl->x && !fl->m
		    && !fl->force && !fl->G && !fl->g && !fl->o && isatty(STDOUT_FILENO))
			mx_output_c(*names);
		if (!isatty(STDOUT_FILENO) && !fl->C && !fl->x && !fl->m
		    && !fl->long_out && !fl->g && !fl->o && !fl->force)
			output_1(*names, fl);
	}
}

static void outputerropen(t_element **args, t_flags *fl) {
	if ((*args)->inner_elements != NULL) {
		mx_output(&(*args)->inner_elements, fl, 1);
		if (fl->recursive) {
			fl->files = true;
			mx_delete_elements(&(*args)->inner_elements, fl);
			if ((*args)->inner_elements) {
				mx_printchar('\n');
				mx_dir(&(*args)->inner_elements, fl);
			}
		}
	} else if ((*args)->error_message != NULL) {
		mx_printerr("uls: ");
		mx_printerr((*args)->path);
		mx_printerr(": ");
		mx_printerr((*args)->error_message);
		mx_printerr("\n");
	}
}

void mx_output_all(t_element ***args, t_flags *fl) {
	if (*args) {
		for (int i = 0; (*args)[i] != NULL; i++) {
			if (fl->files) {
				if ((*args)[i]->path[0] == '/' && (*args)[i]->path[1] == '/')
					mx_printstr(&(*args)[i]->path[1]);
				else
					mx_printstr((*args)[i]->path);
				mx_printchar(':');
				mx_printchar('\n');
			}
			outputerropen(&(*args)[i], fl);
			if (fl->files && (*args)[i + 1])
				mx_printchar('\n');
		}
		mx_del_arr_arr(args);
	}
}
