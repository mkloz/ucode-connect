#include "uls.h"

static char *get_group_name(t_stat *info) {
	struct group *grp = getgrgid(info->st_gid);

	if (grp) {
		return mx_strdup(grp->gr_name);
	}

	return mx_itoa((int) info->st_gid);
}

static char *get_user_name(t_stat *info) {
	struct passwd *pw = getpwuid(info->st_uid);

	if (pw) {
		return mx_strdup(pw->pw_name);
	}

	return mx_itoa((int) info->st_uid);
}

int mx_get_int_length(int number) {
	char *str = mx_itoa(number);
	int length = mx_strlen(str);

	free(str);

	return length;
}

static t_max_len_limits create_max_len(t_element_list *elements) {
	t_max_len_limits size = {0, 0, 0, 0};

	for (t_element_list *el = elements; el; el = el->next) {
		char *group_name = get_group_name(&el->data->info);
		char *user_name = get_user_name(&el->data->info);

		if (size.max_link_len < mx_get_int_length((int) el->data->info.st_nlink))
			size.max_link_len = mx_get_int_length((int) el->data->info.st_nlink);
		if (size.max_size_len < mx_get_int_length((int) el->data->info.st_size)) {
			size.max_size_len = mx_get_int_length((int) el->data->info.st_size);
		}
		if (size.max_group_name_len < mx_strlen(group_name))
			size.max_group_name_len = mx_strlen(group_name);
		if (size.max_username_len < mx_strlen(user_name))
			size.max_username_len = mx_strlen(user_name);
		free(group_name);
		free(user_name);
	}
	return size;
}

static int calculate_total_size(t_element_list *elements) {
	int total_size = 0;

	for (t_element_list *el = elements; el; el = el->next) {
		total_size += (int) el->data->info.st_blocks;
	}

	return total_size;
}

void mx_output_l(t_element_list *elements, bool print_total) {
	t_max_len_limits len = create_max_len(elements);

	if (print_total) {
		mx_printstr("total ");
		mx_printint(calculate_total_size(elements));
		mx_printchar('\n');
	}
	for (t_element_list *el = elements; el; el = el->next) {
		mx_print_line_l(el->data, &len);
	}
}
