#include "uls.h"

static int compare_elements(t_element *first, t_element *second, t_flags *fl) {
	if (fl->S) {
		if (first->info.st_size < second->info.st_size)
			return 1;
		if (first->info.st_size == second->info.st_size)
			return mx_strcmp(first->name, second->name);
	} else if (fl->t && !fl->color_out && !fl->u) {
		if (first->info.st_mtime == second->info.st_mtime) {
			if (first->info.st_mtimespec.tv_nsec
			    == second->info.st_mtimespec.tv_nsec)
				return mx_strcmp(first->name, second->name);
			return (first->info.st_mtimespec.tv_nsec
			        < second->info.st_mtimespec.tv_nsec) ? 1 : 0;
		}
		return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
	}
	if (fl->u && fl->t && !fl->S) {
		if (first->info.st_atime == second->info.st_atime) {
			if (first->info.st_atimespec.tv_nsec
			    == second->info.st_atimespec.tv_nsec)
				return mx_strcmp(first->name, second->name);
			return (first->info.st_atimespec.tv_nsec
			        < second->info.st_atimespec.tv_nsec) ? 1 : 0;
		}
		return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
	}
	if (fl->color_out && fl->t && !fl->S) {
		if (first->info.st_ctime == second->info.st_ctime) {
			if (first->info.st_ctimespec.tv_nsec
			    == second->info.st_ctimespec.tv_nsec)
				return mx_strcmp(first->name, second->name);
			return (first->info.st_ctimespec.tv_nsec
			        < second->info.st_ctimespec.tv_nsec) ? 1 : 0;
		}
		return (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
	} else if (!fl->t && !fl->S)
		if (mx_strcmp(first->name, second->name) > 0)
			return 1;
	return 0;
}


static int get_elements_len(t_element **elm) {
	int i = 0;

	while (elm[i]) {
		i++;
	}
	return i;
}

static void swap_elements(t_element **one, t_element **two) {
	t_element *temp = *one;

	*one = *two;
	*two = temp;
}

void mx_sort_elements(t_element ***disp, t_flags *flags) {
	t_element **el = *disp;
	int size = get_elements_len(el);

	for (int i = 0; i < size; i++) {
		for (int k = i + 1; k < size; k++) {
			if (el[i]->error_message != NULL) {
				if (mx_strcmp(el[i]->name, el[k]->name) == 1)
					swap_elements(&(el[i]), &(el[k]));
			} else if (compare_elements(el[i], el[k], flags) == flags->r) {
				swap_elements(&(el[i]), &(el[k]));
			}
		}
	}
}
