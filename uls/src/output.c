#include "uls.h"

static int get_max_name_size(t_element_list *elements) {
	int max_name_size = 0;

	for (t_element_list *el = elements; el; el = el->next) {
		int temp = mx_strlen(el->data->name);

		if (temp > max_name_size) {
			max_name_size = temp;
		}
	}

	if (max_name_size % 8 == 0) {
		return max_name_size + 8;
	}

	return 8 - (max_name_size % 8) + max_name_size;
}

void mx_print_tab(int len, int max_name_size) {
	int spaces = max_name_size - len;
	int tab_count = (spaces / 8);

	if (spaces % 8 != 0) {
		tab_count++;
	}

	for (int i = 0; i < tab_count; i++) {
		mx_printchar('\t');
	}
}

t_element_list *mx_get_element_by_index(t_element_list *list, int index) {
	if (list == NULL || index < 0) {
		return NULL;
	}

	t_element_list *current = list;
	int current_index = 0;

	while (current != NULL) {
		if (current_index == index) {
			return current;
		}

		current = current->next;
		current_index++;
	}

	return NULL;
}

static void print_table(t_element_list *elements, int rows_count, int elements_count, int max_name_size) {
	for (int i = 0; i < rows_count; i++) {
		for (int j = 0; i + j < elements_count; j += rows_count) {
			t_element_list *el = mx_get_element_by_index(elements, i + j);

			mx_printstr(el->data->name);
			if (el->next && (i + j + rows_count < elements_count))
				mx_print_tab(mx_strlen(el->data->name), max_name_size);
		}
		if (i != rows_count - 1)
			mx_printchar('\n');
	}
}

static void print_names(t_element_list *elements, int max_name_size, int win_columns_size) {
	int cols_count = (win_columns_size / max_name_size) != 0 ? win_columns_size / max_name_size : 1;
	int names_count = mx_list_size((t_list *) elements);

	if (max_name_size * cols_count > win_columns_size && cols_count > 1) {
		cols_count--;
	}
	int rows_count = names_count / cols_count;

	if (rows_count == 0
	    || names_count % cols_count != 0) {
		rows_count++;
	}
	print_table(elements, rows_count, names_count, max_name_size);
	mx_printchar('\n');
}

static void output_one_per_line(t_element_list *elements) {
	for (t_element_list *el = elements; el; el = el->next) {
		mx_printstr(el->data->name);
		mx_printchar('\n');
	}
}

void mx_output_default(t_element_list *elements) {
	int max_name_size = get_max_name_size(elements);
	struct winsize win_size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);

	if (isatty(STDOUT_FILENO)) {
		print_names(elements, max_name_size, win_size.ws_col);
	} else {
		output_one_per_line(elements);
	}
}

void mx_output(t_uls *uls, t_element_list *elements) {
	mx_sort_elements(&elements);

	if (uls->flags->long_out)
		mx_output_l(elements, true);
	else if (uls->flags->one)
		output_one_per_line(elements);
	else
		mx_output_default(elements);
}

void mx_output_files(t_uls *uls, t_element_list *elements) {
	mx_sort_elements(&elements);

	if (uls->flags->long_out)
		mx_output_l(elements, false);
	else if (uls->flags->one)
		output_one_per_line(elements);
	else
		mx_output_default(elements);
}

void mx_output_dirs(t_uls *uls) {
	for (t_element_list *dir = uls->dirs; dir; dir = dir->next) {
		if (uls->elements->next) {
			if (dir->data->path[0] == '/' && dir->data->path[1] == '/')
				mx_printstr(&dir->data->path[1]);
			else
				mx_printstr(dir->data->path);
			mx_printchar(':');
			mx_printchar('\n');
		}
		if (dir->data->inner_elements != NULL) {
			mx_output(uls, dir->data->inner_elements);
		} else if (dir->data->error_message != NULL) {
			mx_printerr("uls: ");
			mx_printerr(dir->data->path);
			mx_printerr(": ");
			mx_printerr(dir->data->error_message);
			mx_printerr("\n");
		}
		if (dir->next) {
			mx_printchar('\n');
		}
	}
}
