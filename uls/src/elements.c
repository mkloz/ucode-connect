#include "uls.h"

void mx_join_path(char **res, char *s2) {
	char *new = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
	int i = 0;
	int si = -1;
	char *s1 = *res;

	while (s1[++si]) {
		new[i] = s1[si];
		i++;
	}
	si = -1;
	while (s2[++si]) {
		new[i] = s2[si];
		i++;
	}
	mx_strdel(&(*res));
	*res = new;
}


t_element_list *mx_get_files(t_element_list *elements) {
	t_element_list *files = NULL;

	for (t_element_list *el = elements; el; el = el->next) {
		if (el->data->error_message == NULL) {
			if (!MX_IS_DIR(el->data->info.st_mode)) {
				mx_push_back((t_list **) &files, el->data);
			}
		}
	}
	return files;
}

t_element_list *mx_get_dirs(t_element_list *elements) {
	t_element_list *dirs = NULL;

	for (t_element_list *el = elements; el; el = el->next) {
		if (el->data->error_message == NULL) {
			if (MX_IS_DIR(el->data->info.st_mode)) {
				mx_push_back((t_list **) &dirs, el->data);
			}
		}
	}
	return dirs;
}

t_element_list *mx_get_errors(t_element_list *elements) {
	t_element_list *errors = NULL;

	for (t_element_list *el = elements; el; el = el->next) {
		if (el->data->error_message != NULL) {
			mx_push_back((t_list **) &errors, el->data);

		}
	}

	return errors;
}

static bool is_hidden(char *name) {
	return mx_strcmp(name, ".") == 0
	       || mx_strcmp(name, "..") == 0
	       || (mx_strlen(name) > 0 && name[0] == '.');
}

static t_element *create_inner_element_node(char *name, char *path) {
	t_element *node = (t_element *) malloc(1 * sizeof(t_element));

	node->name = mx_strdup(name);
	node->path = mx_strdup(path);
	node->error_message = NULL;
	node->inner_elements = NULL;
	mx_join_path(&node->path, "/");
	mx_join_path(&node->path, name);

	if (lstat(node->path, &(node->info)) == -1) {
		node->error_message = mx_strdup(strerror(errno));
	}
	return node;
}

static void fill_all_dirs(t_uls *uls) {
	DIR *dir_stream;
	struct dirent *inner_element;

	for (t_element_list *dir = uls->dirs; dir; dir = dir->next) {
		if ((dir_stream = opendir(dir->data->path)) != NULL) {
			while ((inner_element = readdir(dir_stream))) {
				if (!is_hidden(inner_element->d_name)) {
					mx_push_back((t_list **) &dir->data->inner_elements,
					             create_inner_element_node(inner_element->d_name, dir->data->path));
				}
			}
			closedir(dir_stream);
		} else {
			if (dir->data->error_message) {
				mx_strdel(&dir->data->error_message);
			}
			dir->data->error_message = mx_strdup(strerror(errno));
			uls->exit_code = EXIT_FAILURE;
		}
	}
}

int mx_ls(t_uls *uls) {
	if (uls->errors) {
		mx_output_errors(uls->errors);
	}
	if (uls->files) {
		mx_output_files(uls, uls->files);

		if (uls->dirs) {
			mx_printchar('\n');
		}
	}
	if (uls->dirs) {
		fill_all_dirs(uls);
		mx_output_dirs(uls);
	}
	if (uls->errors) {
		uls->exit_code = EXIT_FAILURE;
	}

	return uls->exit_code;
}
