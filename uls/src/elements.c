#include "uls.h"

void mx_join_path(char **res, char *s2) {
	char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
	int i = 0;
	int si = -1;
	char *s1 = *res;

	while (s1[++si]) {
		newstr[i] = s1[si];
		i++;
	}
	si = -1;
	while (s2[++si]) {
		newstr[i] = s2[si];
		i++;
	}
	mx_strdel(&(*res));
	*res = newstr;
}

static t_element *create_file_node(t_element *args) {
	t_element *node = (t_element *) malloc(1 * sizeof(t_element));

	node->name = mx_strdup(args->name);
	node->path = mx_strdup(args->path);
	if (args->error_message)
		node->error_message = mx_strdup(args->error_message);
	else
		node->error_message = NULL;
	lstat(node->path, &(node->info));
	if (args->inner_elements != NULL)
		node->inner_elements = args->inner_elements;
	else
		node->inner_elements = NULL;
	return node;
}

static void init_arrays(t_element ***files, t_element ***dirs,
                        t_element ***errors, t_element ***args) {
	int j = 0;
	int nDir = 0;
	int nErr = 0;

	for (int i = 0; (*args)[i] != NULL; i++)
		if ((*args)[i]->error_message == NULL) {
			if (!IS_DIR((*args)[i]->info.st_mode)) {
				j++;
			} else
				nDir++;
		} else
			nErr++;
	if (j > 0)
		*files = malloc((j + 1) * sizeof(t_element *));
	if (nDir > 0)
		*dirs = malloc((nDir + 1) * sizeof(t_element *));
	if (nErr > 0)
		*errors = malloc((nErr + 1) * sizeof(t_element *));
}

static t_counters *init_counters() {
	t_counters *num = malloc(sizeof(t_counters));

	num->dir_index = 0;
	num->errors_index = 0;
	num->files_index = 0;
	return num;
}

static void add_element(t_element **args, t_counters *num, t_element ***files, t_element ***dirs) {
	if (!IS_DIR((*args)->info.st_mode)) {
		(*files)[num->files_index++] = create_file_node((*args));
		(*files)[num->files_index] = NULL;
	} else {
		(*dirs)[num->dir_index++] = create_file_node((*args));
		(*dirs)[num->dir_index] = NULL;
	}
}

t_element **mx_get_files(t_element ***args, t_flags *fl) {
	t_element **files = NULL;
	t_element **dirs = NULL;
	t_element **errors = NULL;
	t_counters *num = init_counters();

	init_arrays(&files, &dirs, &errors, args);

	for (int i = 0; (*args)[i] != NULL; i++) {
		if ((*args)[i]->error_message == NULL)
			add_element(&(*args)[i], num, &files, &dirs);
		else {
			errors[num->errors_index++] = create_file_node((*args)[i]);
			errors[num->errors_index] = NULL;
		}
	}
	if (num->dir_index > 1)
		fl->files = true;
	mx_delete_elements_list(args, dirs);
	mx_output_err(&errors, fl);
	free(num);
	return files;
}

static void create_dirs(t_element ***dirs, t_element ***args) {
	int count = 0;

	for (int i = 0; (*args)[i] != NULL; i++)
		if ((*args)[i]->error_message == NULL)
			if (IS_DIR((*args)[i]->info.st_mode) &&
			    mx_strcmp((*args)[i]->name, ".") != 0 &&
			    mx_strcmp((*args)[i]->name, "..") != 0)
				count++;
	if (count > 0)
		*dirs = malloc((count + 1) * sizeof(t_element *));
}

void mx_delete_elements(t_element ***args, t_flags *fl) {
	t_element **dirs = NULL;
	int count = 0;

	create_dirs(&dirs, args);
	for (int i = 0; (*args)[i] != NULL; i++) {
		if ((*args)[i]->error_message == NULL) {
			if (IS_DIR((*args)[i]->info.st_mode) &&
			    mx_strcmp((*args)[i]->name, ".") != 0 &&
			    mx_strcmp((*args)[i]->name, "..") != 0) {
				dirs[count++] = create_file_node((*args)[i]);
				dirs[count] = NULL;
			}
		}
	}
	fl->files = true;
	mx_delete_elements_list(args, dirs);
}

static int is_should_be_hidden(char *name, t_flags *fl) {
	if (fl->show_all_hidden != 1)
		return 0;
	if (mx_strcmp(name, ".") == 0)
		return 0;
	if (mx_strcmp(name, "..") == 0)
		return 0;
	return 1;
}

static int count_read(t_element **arg, t_flags *fl) {
	int count = 0;
	t_element *args = *arg;
	DIR *dptr;
	struct dirent *ds;

	if (IS_DIR(args->info.st_mode) || IS_LNK(args->info.st_mode)) {
		if ((dptr = opendir(args->path)) != NULL) {
			while ((ds = readdir(dptr)) != NULL)
				if (ds->d_name[0] != '.'
				    || is_should_be_hidden(ds->d_name, fl) == 1)
					count++;
			closedir(dptr);
		} else {
			(*arg)->error_message = mx_strdup(strerror(errno));
			fl->ex = true;
			return -1;
		}
	}
	return count;
}

static t_element *create_inner_element_node(char *name, char *path) {
	t_element *node = (t_element *) malloc(1 * sizeof(t_element));

	node->name = mx_strdup(name);
	node->path = mx_strdup(path);
	mx_join_path(&node->path, "/");
	mx_join_path(&node->path, name);
	node->error_message = NULL;
	if (lstat(node->path, &(node->info)) == -1)
		node->error_message = mx_strdup(strerror(errno));
	node->inner_elements = NULL;
	return node;
}

static void open_dir(t_element ***args, t_flags *fl) {
	DIR *dptr;
	struct dirent *ds;
	int count = 0;

	for (int i = 0; (*args)[i] != NULL; i++) {
		count = count_read(&(*args)[i], fl);
		if (count > 0) {
			(*args)[i]->inner_elements = malloc((count + 1) * sizeof(t_element *));
			if ((dptr = opendir((*args)[i]->path)) != NULL) {
				for (count = 0; (ds = readdir(dptr)) != NULL;)
					if (ds->d_name[0] != '.'
					    || is_should_be_hidden(ds->d_name, fl) == 1)
						(*args)[i]->inner_elements[count++] =
								create_inner_element_node(ds->d_name, (*args)[i]->path);
				(*args)[i]->inner_elements[count] = NULL;
				closedir(dptr);
			}
		}
	}
	mx_output_all(args, fl);
}

void mx_dir(t_element ***args, t_flags *flags) {
	t_element **files = mx_get_files(&(*args), flags);

	if (files) {
		mx_output(&files, flags, 0);
		if (*args)
			mx_printchar('\n');
		flags->files = true;
		mx_del_arr_arr(&files);
	}
	if (*args)
		open_dir(&(*args), flags);
}
