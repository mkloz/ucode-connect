#include "../inc/uls.h"

void mx_print_name(char *name, struct stat *buf, t_flags *opts) {
	int istty = isatty(fileno(stdout));
	if (opts->G && istty)
		mx_set_color(buf);
	mx_printstr(name);
	if (istty)
		mx_printstr(MX_COLOR_NRM);
	if (S_ISDIR(buf->st_mode) && (opts->p || opts->F))
		mx_printchar('/');
	else if (S_ISFIFO(buf->st_mode) && opts->F)
		mx_printchar('|');
	else if (S_ISLNK(buf->st_mode) && opts->F)
		mx_printchar('@');
	else if ((buf->st_mode & S_IEXEC) && opts->F)
		mx_printchar('*');
	else if (((buf->st_mode & S_IFMT) == S_IFSOCK) && opts->F)
		mx_printchar('=');
}

void mx_print_m(char **elements, struct winsize *max, char *dir_path, t_flags *opts) {
	int cur_len = 0;
	struct stat buf;
	for (int i = 0; elements[i] != NULL; ++i) {
		if (cur_len + mx_strlen(elements[i]) >= max->ws_col - 1) {
			mx_printchar('\n');
			cur_len = 0;
		}
		char *path = mx_strjoin(dir_path, elements[i]);
		lstat(path, &buf);
		free(path);
		mx_print_name(elements[i], &buf, opts);
		cur_len += (mx_strlen(elements[i]) + 2);
		if (elements[i + 1] != NULL)
			mx_printstr(", ");
		else
			mx_printchar('\n');
	}
	free(dir_path);
}

void mx_print(char **files, struct winsize *max, char *dir_path, t_flags *opts) {
	int istty = isatty(fileno(stdout));

	if (!istty || opts->one) {
		mx_print_strarr(files, "\n");
		return;
	}
	struct stat buf;
	int max_block_size = 1;
	int total = 0;

	int len = 0;
	for (; files[len] != NULL; len++) {
		if (opts->s) {
			char *path = mx_strjoin(dir_path, files[len]);
			lstat(path, &buf);
			total += buf.st_blocks;
			free(path);
			char *block_size_str = mx_itoa(buf.st_blocks);
			if (max_block_size < mx_strlen(block_size_str))
				max_block_size = mx_strlen(block_size_str);
			free(block_size_str);
		}
	}
	int col = mx_get_col(files, len, max->ws_col);
	int rows = len / col;
	if (len % col != 0) {
		rows++;
	}
	int fact_len = len;
	while (fact_len % rows != 0)
		fact_len++;
	col = fact_len / rows;

	int k = 0;
	bool reached_end = false;

	if (opts->s) {
		mx_printstr("total ");
		mx_printint(total);
		mx_printchar('\n');
	}
	for (int i = 0; i < rows; i++) {
		if (opts->C)
			k = i;
		int el_col = 0;
		for (int j = 0; j < col; j++) {
			if (reached_end && j == col - 1)
				break;

			char *path = mx_strjoin(dir_path, files[k]);
			lstat(path, &buf);
			free(path);

			if (opts->s) {
				char *block_size = mx_itoa(buf.st_blocks);
				int block_size_int = mx_strlen(block_size);
				free(block_size);
				for (int k = 0; k < max_block_size - block_size_int; k++)
					mx_printchar(' ');
				mx_printint(buf.st_blocks);
				mx_printchar(' ');
			}
			mx_print_name(files[k], &buf, opts);

			if (files[k + 1] == NULL) {
				reached_end = true;
				break;
			}
			char *tabs = "\t";
			if (rows == 1)
				tabs = "\t";
			else if (j < col - 1)
				tabs = mx_get_tabs(rows, el_col, k, files);

			if (opts->C) {
				k += rows;
				el_col += rows;
			} else {
				k++;
				el_col++;
			}

			if (j < col - 1)
				mx_printstr(tabs);
			if (rows > 1 && j < col - 1)
				free(tabs);
		}
		mx_printchar('\n');
	}

	free(dir_path);
}

void mx_print_l(char **files, char *dir_path, t_flags *opts, bool is_dir) {
	int len = 0;
	for (; files[len] != NULL; ++len);
	if (opts) {};

	struct stat buf;
	char *ntime = mx_strnew(100);
	int links_amount_max_len = 0;
	int max_size_len = mx_get_max_size_len(files, &links_amount_max_len, dir_path);
	int max_block_size_len = 1;
	int max_file_inode_len = 1;
	int total = 0;
	for (int i = 0; i < len; ++i) {
		char *path = mx_strjoin(dir_path, files[i]);
		stat(path, &buf);
		total += buf.st_blocks;
		if (opts->s) {
			char *new_block_size = mx_itoa(buf.st_blocks);
			if (max_block_size_len < mx_strlen(new_block_size))
				max_block_size_len = mx_strlen(new_block_size);
			free(new_block_size);
		}
		if (opts->i) {
			char *new_file_inode_str = mx_itoa(buf.st_ino);
			if (max_file_inode_len < mx_strlen(new_file_inode_str))
				max_file_inode_len = mx_strlen(new_file_inode_str);
			free(new_file_inode_str);
		}
	}
	if (is_dir) {
		mx_printstr("total ");
		mx_printint(total);
		mx_printchar('\n');
	}

	for (int i = 0; i < len; ++i) {
		char *path = mx_strjoin(dir_path, files[i]);
		lstat(path, &buf);

		if (opts->i) {
			char *file_inode_str = mx_itoa(buf.st_ino);
			int file_inode_len = mx_strlen(file_inode_str);
			free(file_inode_str);

			for (int k = 0; k < max_file_inode_len - file_inode_len; k++) {
				mx_printchar(' ');
			}

			mx_printint(buf.st_ino);
			mx_printchar(' ');
		}

		if (opts->s) {
			char *block_size = mx_itoa(buf.st_blocks);
			int block_size_int = mx_strlen(block_size);
			free(block_size);

			for (int k = 0; k < max_block_size_len - block_size_int; k++) {
				mx_printchar(' ');
			}

			mx_printint(buf.st_blocks);
			mx_printchar(' ');
		}

		if (S_ISDIR(buf.st_mode))
			mx_printchar('d');
		if (S_ISREG(buf.st_mode))
			mx_printchar('-');
		if (S_ISFIFO(buf.st_mode))
			mx_printchar('p');
		if (S_ISLNK(buf.st_mode))
			mx_printchar('l');
		if (S_ISBLK(buf.st_mode))
			mx_printchar('b');
		if (S_ISCHR(buf.st_mode))
			mx_printchar('c');
		if ((buf.st_mode & S_IFMT) == S_IFSOCK)
			mx_printchar('s');

		char *permissions = mx_get_permisions_string(&buf, path);
		mx_printstr(permissions);
		free(permissions);
		mx_printchar(' ');

		for (int k = mx_strlen(mx_itoa(buf.st_nlink)); k < links_amount_max_len; ++k)
			mx_printchar(' ');
		mx_printint(buf.st_nlink);
		mx_printchar(' ');

		struct passwd *ubuf = getpwuid(buf.st_uid);
		if (ubuf == NULL) {
			char *mx_err = "uls";
			perror(mx_err);
			free(dir_path);
			exit(1);
		}
		mx_printstr(ubuf->pw_name);
		mx_printstr("  ");

		if (!opts->o) {
			struct group *gbuf = getgrgid(buf.st_gid);
			if (gbuf == NULL) {
				char *mx_err = "uls";
				perror(mx_err);
				free(dir_path);
				exit(1);
			}
			mx_printstr(gbuf->gr_name);
			mx_printstr("  ");
		}

		for (int k = mx_strlen(mx_itoa(buf.st_size)); k < max_size_len; ++k)
			mx_printchar(' ');
		mx_printint(buf.st_size);
		mx_printchar(' ');

		mx_strcpy(ntime, ctime(&buf.st_mtime));
		if (!opts->T) {
			char *mtime = mx_get_mtime(ntime);
			mx_printstr(mtime);
			free(mtime);
		} else {
			char *ntime_full = mx_strnew(20);
			ntime_full = mx_strncpy(ntime_full, ntime + 4, 20);
			mx_printstr(ntime_full);
			free(ntime_full);
		}
		mx_printchar(' ');

		mx_print_name(files[i], &buf, opts);

		if (S_ISLNK(buf.st_mode)) {
			char link_buf[1024];
			ssize_t len;
			if ((len = readlink(path, link_buf, sizeof(link_buf) - 1)) != -1) {
				link_buf[len] = '\0';
				mx_printstr(" -> ");
				mx_printstr(link_buf);
			}
		}
		mx_printchar('\n');
		free(path);
	}
	free(dir_path);
	free(ntime);
}

void mx_print_dirs(char **elements, int n, struct winsize max, t_flags *opts) {
	DIR *dir = NULL;
	struct dirent *sd = NULL;
	char *str;
	for (int i = 0; elements[i] != NULL; i++) {
		if (n > 1) {
			mx_printstr(elements[i]);
			mx_printstr(":\n");
			dir = opendir(elements[i]);
		} else
			dir = opendir(elements[i]);

		if (dir == NULL) {
			mx_printerr("uls");
			exit(1);
		}

		str = NULL;
		while ((sd = readdir(dir)) != NULL) {
			str = mx_strjoin(str, sd->d_name);
			str = mx_strjoin(str, " ");
		}

		char **files = NULL;
		files = mx_strsplit(str, ' ');

		if (!opts->f)
			mx_sort_strarr(files, opts);
		if ((!opts->a && opts->A) || (!opts->a && !opts->A))
			files = mx_exclude_hidden(files, opts);
		free(str);

		if (!opts->f) {
			if (opts->t)
				mx_sort_t(files, mx_strjoin(elements[i], "/"), opts);
			else if (opts->S)
				mx_sort_S(files, mx_strjoin(elements[i], "/"), opts);
		}

		if (files != NULL) {
			if (opts->m)
				mx_print_m(files, &max, mx_strjoin(elements[i], "/"), opts);
			else if (opts->C || opts->x)
				mx_print(files, &max, mx_strjoin(elements[i], "/"), opts);
			else
				mx_print_l(files, mx_strjoin(elements[i], "/"), opts, true);

			mx_del_strarr(&files);
		}
		closedir(dir);

		if (n > 1 && elements[i + 1] != NULL) {
			mx_printchar('\n');
		}
	}
}
