#include "uls.h"

static void mx_fill_default_flags(t_flags **fl) {
	(*fl)->x = 0;
	(*fl)->long_out = 0;
	(*fl)->C = 0;
	(*fl)->m = 0;
	(*fl)->force = 0;
}

static void mx_throw_wrong_flag_err(t_flags **fl, char flag) {
	mx_printerr("uls: illegal option -- ");
	mx_printchar_err(flag);
	mx_printerr("\n");
	mx_printerr("usage: uls [-ACGRSTcfglmortux1] [file ...]\n");
	free(*fl);
	fl = NULL;

	exit(EXIT_FAILURE);
}

static void add_flags(t_flags **fl, char flag) {
	mx_fill_default_flags(fl);

	if (flag == 'T') {
		(*fl)->T = true;
	} else if (flag == 'G' && isatty(STDOUT_FILENO)) {
		(*fl)->G = true;
	} else if (flag == 'c') {
		(*fl)->u = false;
		(*fl)->color_out = true;
	} else if (flag == 't') {
		(*fl)->t = true;
	} else if (flag == 'u') {
		(*fl)->u = true;
		(*fl)->color_out = false;
	} else if (flag == 'S') {
		(*fl)->S = true;
	} else if (flag == 'r') {
		(*fl)->r = false;
	} else if (flag == 'G' && !isatty(STDOUT_FILENO)) {
		(*fl)->G = false;
	} else if (flag == 'R') {
		(*fl)->recursive = true;
	} else if (flag == 'A') {
		(*fl)->show_all_hidden = true;
	} else if (flag == 'g') {
		(*fl)->g = true;
		(*fl)->long_out = true;
	} else if (flag == 'o') {
		(*fl)->o = true;
		(*fl)->long_out = true;
	} else if (flag == 'l')
		(*fl)->long_out = true;
	else if (flag == 'C')
		(*fl)->C = true;
	else if (flag == '1')
		(*fl)->force = true;
	else if (flag == 'x')
		(*fl)->x = true;
	else if (flag == 'm')
		(*fl)->m = true;
	else mx_throw_wrong_flag_err(fl, flag);
}

t_flags *mx_get_flags(char *argv[], int *i) {
	t_flags *fl = malloc(sizeof(t_flags));

	fl->r = true;
	while (argv[(*i)]) {
		if (argv[(*i)][0] == '-') {
			if (argv[(*i)][1] == '-') {
				(*i)++;
				break;
			}
			if (argv[(*i)][1] == '\0')
				break;
			for (int j = 1; argv[(*i)][j]; j++) {
				add_flags(&fl, argv[(*i)][j]);
			}
		} else
			break;
		(*i)++;
	}
	return fl;
}

static t_element *create_element_node(char *data) {
	t_element *node = (t_element *) malloc(1 * sizeof(t_element));

	node->name = mx_strdup(data);
	node->path = mx_strdup(data);
	node->error_message = NULL;
	if (lstat(data, &(node->info)) == -1)
		node->error_message = mx_strdup(strerror(errno));
	node->inner_elements = NULL;

	return node;
}

static t_element **names_array_to_list(char **name, int count) {
	t_element **new = malloc(count * sizeof(t_element *));
	int i = 0;

	for (i = 0; name[i]; i++)
		new[i] = create_element_node(name[i]);
	new[i] = NULL;
	return new;
}

static char **parse_names(int argc, char **argv, int i, int *count) {
	int j = i;
	char **names = NULL;

	if (i == argc) {
		*count = 2;
		names = malloc(2 * sizeof(char *));
		names[0] = mx_strdup(".");
		names[1] = NULL;
	} else {
		for (; argv[j]; j++);

		names = malloc((j - i + 1) * sizeof(char *));
		for (j = 0; argv[i]; i++, j++) {
			names[j] = mx_strdup(argv[i]);
		}
		names[j] = NULL;
		*count = j + 1;
	}
	return names;
}

t_element **mx_get_names(int argc, char **argv, int i) {
	int count = 0;
	char **name = parse_names(argc, argv, i, &count);
	t_element **args = names_array_to_list(name, count);

	mx_del_strarr(&name);
	return args;
}
