#include "uls.h"

static void get_user_name(t_element *print, int usr) {
	struct passwd *pw = getpwuid(print->info.st_uid);
	int counter = 0;
	char *name = NULL;

	if (pw)
		name = mx_strdup(pw->pw_name);
	else
		name = mx_itoa(print->info.st_uid);
	if (mx_strlen(name) == usr)
		mx_printstr(name);
	else if (mx_strlen(name) < usr) {
		counter = mx_strlen(name);
		mx_printstr(name);
		while (counter != usr) {
			mx_printchar(' ');
			counter++;
		}
	}
	mx_printstr("  ");
	free(name);
}

static void get_group_name(t_element *print, int group) {
	struct group *grp = getgrgid(print->info.st_gid);
	int counter = 0;
	char *name = NULL;

	if (grp)
		name = mx_strdup(grp->gr_name);
	else
		name = mx_itoa(print->info.st_gid);
	if (mx_strlen(name) == group)
		mx_printstr(name);
	else if (mx_strlen(name) < group) {
		counter = mx_strlen(name);
		mx_printstr(name);
		while (counter != group) {
			mx_printchar(' ');
			counter++;
		}
	}
	mx_printstr("  ");
	free(name);
}

static void print_link_and_color(t_element *print, t_flags *flags) {
	if (flags->G)
		mx_printstr_g(print);
	else if (IS_LNK(print->info.st_mode)) {
		mx_printstr(print->name);
		mx_print_symb_link(print);
	} else
		mx_printstr(print->name);
}

static void print_edit_time(t_element *print, char *t, t_flags *flags) {
	int i = 0;

	if (flags->T)
		for (i = 4; i < t[i]; i++)
			mx_printchar(t[i]);
	else {
		if (1565913600 >= print->info.st_mtime) {
			for (i = 4; i < 10; i++)
				mx_printchar(t[i]);
			mx_printstr("  ");
			for (i = 20; i < 24; i++)
				mx_printchar(t[i]);
		} else
			for (i = 4; i < 16; i++)
				mx_printchar(t[i]);
	}
	mx_printstr(" ");
}

static void print_link(t_element *print, t_element_size *size) {
	int counter = 0;
	char *res_itoa_now = mx_itoa(print->info.st_nlink);
	char *res_itoa_lnk = mx_itoa(size->lnk);

	if (mx_strlen(res_itoa_now) == mx_strlen(res_itoa_lnk)) {
		mx_printint(print->info.st_nlink);
	} else if (mx_strlen(res_itoa_now) < mx_strlen(res_itoa_lnk)) {
		counter = mx_strlen(res_itoa_now);
		while (counter != mx_strlen(res_itoa_lnk)) {
			mx_printchar(' ');
			counter++;
		}
		mx_printint(print->info.st_nlink);
	}
	mx_printchar(' ');
	free(res_itoa_now);
	free(res_itoa_lnk);
}

void mx_print_symb_link(t_element *print) {
	char *buf = NULL;
	ssize_t nbytes = 0;
	ssize_t buf_size = 0;

	buf_size = print->info.st_size == 0 ? 100 : print->info.st_size + 1;
	buf = mx_strnew(buf_size);
	nbytes = readlink(print->path, buf, buf_size);
	mx_printstr(" -> ");
	if (nbytes >= 0)
		mx_printstr(buf);
	mx_strdel(&buf);
}

void mx_print_all(t_element *print, t_element_size *size, t_flags *fl) {
	time_t *chtime = &print->info.st_ctime;
	time_t *atime = &print->info.st_atime;
	time_t *t = &print->info.st_mtime;

	mx_print_permission(print);
	print_link(print, size);
	if ((fl->long_out && !fl->g) || (fl->o && !fl->g))
		get_user_name(print, size->usr);
	if ((fl->long_out && !fl->o) || (fl->g && !fl->o))
		get_group_name(print, size->group);
	mx_print_size(print, size);
	if (fl->u)
		t = atime;
	if (fl->color_out)
		t = chtime;
	print_edit_time(print, ctime(t), fl);
	print_link_and_color(print, fl);
	mx_printchar('\n');
}

static void print_element_name(t_element *args) {
	mx_printstr(args->name);
	mx_printstr(MX_COLOR_RESET);
}

static int print_first_line(t_element *args) {
	if (IS_DIR(args->info.st_mode)) {
		mx_printstr("\033[34m");
		print_element_name(args);
		return 1;
	} else if (IS_LNK(args->info.st_mode)) {
		mx_printstr("\033[35m");
		print_element_name(args);
		return 1;
	} else if (args->info.st_mode & S_IXOTH) {
		mx_printstr(MX_COLOR_RED);
		print_element_name(args);
		return 1;
	}
	return 0;
}

static int print_second_line(t_element *args) {
	if (IS_BLK(args->info.st_mode)) {
		mx_printstr("\033[34;46m");
		print_element_name(args);
		return 1;
	} else if (IS_CHR(args->info.st_mode)) {
		mx_printstr("\033[34;43m");
		print_element_name(args);
		return 1;
	} else if (IS_SOCK(args->info.st_mode)) {
		mx_printstr("\033[32m");
		print_element_name(args);
		return 1;
	}
	return 0;
}

void mx_printstr_g(t_element *args) {
	if (print_first_line(args) == 1) {
	} else if (print_second_line(args) == 1) {
	} else if (IS_FIFO(args->info.st_mode)) {
		mx_printstr("\033[33m");
		print_element_name(args);
	} else if (IS_WHT(args->info.st_mode)) {
		mx_printstr("\033[36m");
		print_element_name(args);
	} else if (IS_EXEC(args->info.st_mode)) {
		mx_printstr("\033[31m");
		print_element_name(args);
	} else
		mx_printstr(args->name);
}

static char get_file_acl(t_element *print) {
	acl_t tmp;

	if (listxattr(print->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_file(print->path, ACL_TYPE_EXTENDED))) {
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

static char check_permition(t_element *print) {
	if (IS_DIR(print->info.st_mode))
		return 'd';
	if (IS_LNK(print->info.st_mode))
		return 'l';
	if (IS_BLK(print->info.st_mode))
		return 'b';
	if (IS_CHR(print->info.st_mode))
		return 'c';
	if (IS_FIFO(print->info.st_mode))
		return 'p';
	if (IS_SOCK(print->info.st_mode))
		return 's';
	if (IS_WHT(print->info.st_mode))
		return 'w';
	return '-';
}

static char check_chmode1(char chmod) {
	if (chmod == '-')
		return chmod = 'S';
	else
		return chmod = 's';
}

static char check_chmode2(char *chmod) {
	if (chmod[9] == '-')
		return chmod[9] = 'T';
	else
		return chmod[9] = 't';
}

void mx_print_permission(t_element *print) {
	char chmod[12];

	chmod[0] = check_permition(print);
	chmod[1] = (S_IRUSR & print->info.st_mode) ? 'r' : '-';
	chmod[2] = (S_IWUSR & print->info.st_mode) ? 'w' : '-';
	chmod[3] = (S_IXUSR & print->info.st_mode) ? 'x' : '-';
	chmod[4] = (S_IRGRP & print->info.st_mode) ? 'r' : '-';
	chmod[5] = (S_IWGRP & print->info.st_mode) ? 'w' : '-';
	chmod[6] = (S_IXGRP & print->info.st_mode) ? 'x' : '-';
	chmod[7] = (S_IROTH & print->info.st_mode) ? 'r' : '-';
	chmod[8] = (S_IWOTH & print->info.st_mode) ? 'w' : '-';
	chmod[9] = (S_IXOTH & print->info.st_mode) ? 'x' : '-';
	chmod[10] = get_file_acl(print);
	chmod[11] = '\0';
	S_ISUID & print->info.st_mode ? chmod[3] = check_chmode1(chmod[3]) : 0;
	S_ISGID & print->info.st_mode ? chmod[6] = check_chmode1(chmod[6]) : 0;
	S_ISVTX & print->info.st_mode ? chmod[9] = check_chmode2(chmod) : 0;
	for (int i = 0; chmod[i]; i++)
		mx_printchar(chmod[i]);
	mx_printchar(' ');
}

static void print_spaces(int size) {
	for (int i = 0; i <= size; i++) {
		mx_printchar(' ');
	}
}

static char *minor_to_hex(char *minor) {
	char *hex_minor = mx_strdup("0x00000000");

	mx_strcpy(hex_minor + (10 - mx_strlen(minor)), minor);
	mx_strdel(&minor);
	return hex_minor;
}

static char *mx_get_minor(t_element *print) {
	int minor_num = (int) (print->info.st_rdev & 0xffffff);
	char *minor = NULL;

	if (minor_num > 255)
		minor = minor_to_hex(mx_nbr_to_hex(minor_num));
	else
		minor = mx_itoa(minor_num);
	return minor;
}

static char *mx_get_major(t_element *print) {
	return mx_itoa((int) (((unsigned int) print->info.st_rdev >> 24) & 0xff));
}

static void print_two_rows(t_element *print, t_element_size *size) {
	char *major = mx_get_major(print);
	char *minor = mx_get_minor(print);

	if (size->is_dev == true)
		if (IS_BLK(print->info.st_mode) || IS_CHR(print->info.st_mode)) {
			print_spaces(2 - mx_strlen(major));
			mx_printstr(major);
			mx_printchar(',');
			mx_printchar(' ');
			print_spaces(2 - mx_strlen(minor));
			mx_printstr(minor);
		} else {
			mx_printstr("       ");
			mx_printint(print->info.st_size);
		}
	else
		mx_printint(print->info.st_size);
	free(major);
	free(minor);
}

void mx_print_size(t_element *print, t_element_size *size) {
	char *res_now = mx_itoa(print->info.st_size);
	char *res_sz = mx_itoa(size->size);
	int counter = 0;

	if (mx_strlen(res_now) == mx_strlen(res_sz))
		print_two_rows(print, size);
	else if (mx_strlen(res_now) < mx_strlen(res_sz)) {
		counter = mx_strlen(res_now);
		while (counter != mx_strlen(res_sz)) {
			mx_printchar(' ');
			counter++;
		}
		print_two_rows(print, size);
	}
	mx_printchar(' ');
	free(res_now);
	free(res_sz);
}
