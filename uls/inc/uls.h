#ifndef MKLOZ_ULS
#define MKLOZ_ULS

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include "libmx.h"

extern int errno;

#define MX_COLOR_NRM  "\x1B[0m"
#define MX_COLOR_RED  "\x1B[31m"
#define MX_COLOR_GRN  "\x1B[32m"
#define MX_COLOR_BRN  "\x1B[33m"
#define MX_COLOR_BLU  "\x1B[34m"
#define MX_COLOR_MAG  "\x1B[35m"
#define MX_COLOR_CYN  "\x1B[36m"

typedef struct s_flags {
	bool one;
	bool A;
	bool a;
	bool C;
	bool F;
	bool f;
	bool G;
	bool i;
	bool l;
	bool m;
	bool o;
	bool p;
	bool r;
	bool S;
	bool s;
	bool T;
	bool t;
	bool x;
} t_flags;

void mx_throw_usage(void);
void mx_init_flags(t_flags *opts);
char **mx_exclude_hidden(char **arr, t_flags *opts);
char **mx_get_elements(int argc, char **argv);
void mx_parse_elements(char **elements, int n, char ***directories, char ***files);
char *mx_get_tabs(int rows, int col, int curr, char **files);
int mx_get_col(char **el, int n, int ws_col);
void mx_get_flags(int argc, char **argv, t_flags *opts);
void mx_check_flag(char c, t_flags *opts);
char *mx_get_mtime(char *ntime);
int mx_get_max_size_len(char **files, int *max_links_amount_len, char *dir_path);
char *mx_get_permisions_string(struct stat *buf, char *path);
int mx_get_xattr(char *file);
char *mx_get_acl(const char *file);
void mx_set_color(struct stat *buf);

void mx_strarr_reverse(char **arr);
void mx_sort_strarr(char **arr, t_flags *opts);
void mx_sort_t(char **arr, char *dir_path, t_flags *opts);
void mx_sort_S(char **arr, char *dir_path, t_flags *opts);

void mx_print_name(char *name, struct stat *buf, t_flags *opts);
void mx_print_m(char **elements, struct winsize *max, char *dir_path, t_flags *opts);
void mx_uls(char **elements, t_flags *opts);
void mx_flag_l(char *dir_name);
void mx_print_dirs(char **elements, int n, struct winsize max, t_flags *opts);
void mx_print(char **files, struct winsize *max, char *dir_path, t_flags *opts);
void mx_print_l(char **files, char *dir_path, t_flags *opts, bool is_dir);

#endif
