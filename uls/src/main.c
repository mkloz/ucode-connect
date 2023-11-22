#include "../inc/uls.h"

void mx_uls(char **elements, t_flags *opts) {
	struct winsize max;
	ioctl(0, TIOCGWINSZ, &max);

	int n = 0;
	char **directories = NULL;
	char **files = NULL;

	if (elements != NULL) {
		for (; elements[n] != NULL; n++);
	} else {
		elements = (char **) malloc(1);
		n = 1;
		elements[0] = mx_strdup(".");
		elements[1] = NULL;
	}

	mx_parse_elements(elements, n, &directories, &files);

	if (files != NULL) {
		if (opts->m)
			mx_print_m(files, &max, NULL, opts);
		else if (opts->C || opts->x)
			mx_print(files, &max, NULL, opts);
		else if (opts->l)
			mx_print_l(files, NULL, opts, false);
		if (directories != NULL)
			mx_printchar('\n');
		mx_del_strarr(&files);
	}
	if (directories != NULL) {
		mx_print_dirs(directories, n, max, opts);
		mx_del_strarr(&directories);
	}
	free(opts);

	if (elements != NULL) {
		mx_del_strarr(&elements);
	}
}


int main(int argc, char *argv[]) {
	t_flags *opts = (t_flags *) malloc(sizeof(t_flags));

	mx_init_flags(opts);
	mx_get_flags(argc, argv, opts);
	char **elements = mx_get_elements(argc, argv);

	if (elements != NULL) {
		if (!opts->f) {
			mx_sort_strarr(elements, opts);

			if (opts->t)
				mx_sort_t(elements, mx_strjoin(".", "/"), opts);
			else if (opts->S)
				mx_sort_S(elements, mx_strjoin(".", "/"), opts);
		}
	}

	mx_uls(elements, opts);

	return 0;
}

