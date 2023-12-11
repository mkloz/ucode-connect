#include "uls.h"

static void print_spaces(int size) {
	for (int i = 0; i < size; i++) {
		mx_printchar(' ');
	}
}

static void print_user_name(t_stat *info, int usr) {
	struct passwd *pw = getpwuid(info->st_uid);
	char *name = NULL;

	if (pw) {
		name = mx_strdup(pw->pw_name);
	} else {
		name = mx_itoa((int) info->st_uid);
	}
	mx_printstr(name);
	print_spaces(usr - mx_strlen(name));
	free(name);
}

static void print_group_name(t_stat *info, int max_group_size) {
	struct group *grp = getgrgid(info->st_gid);
	char *name = NULL;

	if (grp) {
		name = mx_strdup(grp->gr_name);
	} else {
		name = mx_itoa((int) info->st_gid);
	}
	mx_printstr(name);
	print_spaces(max_group_size - mx_strlen(name));
	free(name);
}

static void print_time(t_stat *info) {
	char *element_time_str = ctime(&info->st_mtime);

	time_t current = time(NULL);
	time_t diff = (current - info->st_mtime) > 0 ? current - info->st_mtime : info->st_mtime - current;
	char *result = NULL;

	if (diff > MX_HALF_OF_YEAR_IN_SECONDS) {
		char *tmp = mx_strndup(&element_time_str[4], 7);
		result = mx_strjoin(tmp, &element_time_str[19]);
		result[mx_strlen(result) - 1] = '\0';

		free(tmp);
	} else {
		result = mx_strndup(&element_time_str[4], 12);
	}

	mx_printstr(result);
	free(result);
}

static void print_links_count(t_stat *info, int max_links_count_size) {
	print_spaces(max_links_count_size - mx_get_int_length((int) info->st_nlink));
	mx_printint((int) info->st_nlink);
}

static void print_symbol_link(t_element *element) {
	char *buf = NULL;
	ssize_t bytes_read = 0;
	ssize_t buf_size = 0;

	buf_size = element->info.st_size == 0 ? 100 : element->info.st_size + 1;
	buf = mx_strnew((int) buf_size);
	bytes_read = readlink(element->path, buf, buf_size);

	mx_printstr(" -> ");

	if (bytes_read >= 0) {
		mx_printstr(buf);
	}
	mx_strdel(&buf);
}

static void print_link(t_element *element) {
	if (MX_IS_LNK(element->info.st_mode)) {
		mx_printstr(element->name);
		print_symbol_link(element);
	} else {
		mx_printstr(element->name);
	}
}

static char get_acl(char *path) {
	acl_t acl;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0) {
		return ('@');
	}
	if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED))) {
		acl_free(acl);
		return ('+');
	}
	return (' ');
}

static char check_element_type(t_element *print) {
	if (MX_IS_DIR(print->info.st_mode))
		return 'd';
	if (MX_IS_LNK(print->info.st_mode))
		return 'l';
	if (MX_IS_BLK(print->info.st_mode))
		return 'b';
	if (MX_IS_CHR(print->info.st_mode))
		return 'c';
	if (MX_IS_FIFO(print->info.st_mode))
		return 'p';
	if (MX_IS_SOCK(print->info.st_mode))
		return 's';
	if (MX_IS_WHT(print->info.st_mode))
		return 'w';
	return '-';
}

static void print_permission(t_element *element) {
	int mode = (int) element->info.st_mode;
	char chmod[12] = {check_element_type(element), (S_IRUSR & mode) ? 'r' : '-',
	                  (S_IWUSR & mode) ? 'w' : '-',
	                  (S_IXUSR & mode) ? 'x' : '-',
	                  (S_IRGRP & mode) ? 'r' : '-',
	                  (S_IWGRP & mode) ? 'w' : '-',
	                  (S_IXGRP & mode) ? 'x' : '-',
	                  (S_IROTH & mode) ? 'r' : '-',
	                  (S_IWOTH & mode) ? 'w' : '-',
	                  (S_IXOTH & mode) ? 'x' : '-',
	                  get_acl(element->path),
	                  '\0'};

	if (S_ISUID & mode) chmod[3] = (chmod[3] == '-') ? 'S' : 's';
	if (S_ISGID & mode) chmod[6] = (chmod[6] == '-') ? 'S' : 's';
	if (S_ISVTX & mode) chmod[9] = (chmod[9] == '-') ? 'T' : 't';

	mx_printstr(chmod);
}

static char *get_size(t_stat *info) {
	if (MX_IS_BLK(info->st_mode) || MX_IS_CHR(info->st_mode)) {
		if (info->st_rdev == 0) {
			return mx_itoa((int) info->st_rdev);
		}
		return mx_strjoin("0x", mx_nbr_to_hex(info->st_rdev));
	}

	return mx_itoa((int) info->st_size);
}

static void print_size(t_stat *info, int max_size_len) {
	char *size_str = get_size(info);

	print_spaces(max_size_len - mx_strlen(size_str));
	mx_printstr(size_str);
	free(size_str);
}

void mx_print_line_l(t_element *print, t_max_len_limits *len) {
	print_permission(print);
	mx_printchar(' ');
	print_links_count(&print->info, len->max_link_len);
	mx_printchar(' ');
	print_user_name(&print->info, len->max_username_len);
	mx_printstr("  ");
	print_group_name(&print->info, len->max_group_name_len);
	mx_printstr("  ");
	print_size(&print->info, len->max_size_len);
	mx_printchar(' ');
	print_time(&print->info);
	mx_printstr(" ");
	print_link(print);
	mx_printchar('\n');
}
