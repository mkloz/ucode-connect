#include "uls.h"

static void throw_wrong_flag_err(t_flags **fl, char flag) {
	mx_printerr("uls: illegal option -- ");
	mx_print_char_err(flag);
	mx_printerr("\n");
	mx_printerr("usage: uls [-l1] [file ...]\n");
	free(*fl);
	fl = NULL;

	exit(EXIT_FAILURE);
}

static void add_flag(t_flags **fl, char flag) {
	t_flags *flags = *fl;

	switch (flag) {
		case 'l':
			flags->long_out = true;
			flags->one = false;
			break;
		case '1':
			flags->one = true;
			flags->long_out = false;
			break;
		default:
			throw_wrong_flag_err(fl, flag);
	}
}

t_flags *mx_create_flags(void) {
	t_flags *fl = malloc(sizeof(t_flags));
	fl->long_out = false;
	fl->one = false;

	return fl;
}

t_flags *mx_parse_flags(char *flag_string) {
	t_flags *fl = mx_create_flags();

	if (flag_string[0] == '-') {
		if (flag_string[1] == '-'
		    || flag_string[1] == '\0') {
			return fl;
		}

		for (int j = 1; flag_string[j]; j++) {
			add_flag(&fl, flag_string[j]);
		}
	}
	return fl;
}

static t_element *create_element(char *data) {
	t_element *node = (t_element *) malloc(1 * sizeof(t_element));

	node->name = mx_strdup(data);
	node->path = mx_strdup(data);
	node->error_message = NULL;
	if (lstat(data, &(node->info)) == -1) {
		node->error_message = mx_strdup(strerror(errno));
	}
	node->inner_elements = NULL;

	return node;
}

static t_element_list *parse_names(char **name) {
	t_element_list *list = NULL;

	for (int i = 0; name[i] != NULL; i++) {
		mx_push_back((t_list **) &list, create_element(name[i]));
	}
	return list;
}

static char **extract_names(int argc, char *argv[]) {
	char **names = NULL;

	if (argc == 1
	    || (argc == 2 && argv[1][0] == '-')) {
		names = malloc(2 * sizeof(char *));
		names[0] = mx_strdup(".");
		names[1] = NULL;
	} else {
		int start_index = 1;

		if (argv[1][0] == '-') {
			start_index = 2;
		}

		names = malloc((argc - start_index + 1) * sizeof(char *));
		names[argc - start_index] = NULL;

		for (int i = 0; i + start_index < argc; i++) {
			names[i] = mx_strdup(argv[i + start_index]);
		}
	}
	return names;
}

t_element_list *mx_parse_elements(int argc, char *argv[]) {
	char **names = extract_names(argc, argv);
	t_element_list *elements = parse_names(names);

	mx_del_strarr(&names);
	return elements;
}
