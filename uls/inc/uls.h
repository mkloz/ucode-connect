#ifndef ULS_HEADER_H
#define ULS_HEADER_H

#include "libmx.h"
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

#define IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define IS_EXEC(mode) ((mode) & S_IXUSR)

#define MX_COLOR_RED        "\x1b[31m"
#define MX_COLOR_RESET      "\x1b[0m"

typedef struct s_flags {
	bool long_out;
	bool C;
	bool x;
	bool recursive;
	bool r;
	bool t;
	bool u;
	bool color_out;
	bool S;
	bool show_hidden;
	bool show_all_hidden;
	bool force;
	bool m;
	bool files;
	bool G;
	bool T;
	bool g;
	bool o;
	bool ex;
} t_flags;

typedef struct s_element_size {
	int lnk;
	int size;
	int group;
	int usr;
	bool is_dev;
} t_element_size;

typedef struct s_element {
	char *name;
	char *path;
	char *error_message;
	struct stat info;
	struct s_element **inner_elements;
} t_element;

typedef struct s_counters {
	int files_index;
	int dir_index;
	int errors_index;
} t_counters;

t_flags *mx_get_flags(char *argv[], int *i);

void mx_printstr_g(t_element *args);

int max_len_names(t_element **names);

void mx_print_tab(int len, int maxlen);

void mx_del_arr_arr(t_element ***args);

void mx_printchar_err(char c);

t_element **mx_get_names(int argc, char **argv, int i);

void mx_dir(t_element ***args, t_flags *flags);

void mx_output_all(t_element ***args, t_flags *fl);

void mx_join_path(char **res, char *s2);

void mx_sort_elements(t_element ***disp, t_flags *flags);

t_element **mx_get_files(t_element ***args, t_flags *fl);

void mx_delete_elements(t_element ***args, t_flags *fl);

void mx_delete_elements_list(t_element ***args, t_element **dirs);

void mx_output(t_element ***names, t_flags *fl, int flag);

void mx_output_err(t_element ***error, t_flags *fl);

void mx_output_x(t_element **names);

void mx_output_c(t_element **names);

void mx_output_m(t_element **names, t_flags *fl);

void mx_output_g(t_element **names, t_flags *fl);

void mx_output_l(t_element **names, t_flags *fl, int flag);

void mx_print_permission(t_element *print);

void mx_print_size(t_element *print, t_element_size *size);

void mx_print_symb_link(t_element *print);

void mx_print_all(t_element *print, t_element_size *size, t_flags *fl);

#endif
