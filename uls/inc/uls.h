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

#define MX_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define MX_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define MX_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define MX_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define MX_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define MX_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)

#define MX_HALF_OF_YEAR_IN_SECONDS 15768000

typedef struct s_element t_element;
typedef struct stat t_stat;

typedef struct s_flags {
	bool long_out;
	bool one;
} t_flags;

typedef struct s_max_len_limits {
	int max_link_len;
	int max_size_len;
	int max_group_name_len;
	int max_username_len;
} t_max_len_limits;

typedef struct s_element_list {
	t_element *data;
	struct s_element_list *next;
} t_element_list;

typedef struct s_element {
	char *name;
	char *path;
	char *error_message;
	t_stat info;
	t_element_list *inner_elements;
} t_element;

typedef struct s_uls {
	t_element_list *elements;
	t_element_list *files;
	t_element_list *dirs;
	t_element_list *errors;
	t_flags *flags;
	int exit_code;
} t_uls;

void mx_delete_element(t_element *el);

t_element_list *mx_get_errors(t_element_list *elements);

t_element_list *mx_get_dirs(t_element_list *elements);

t_element_list *mx_get_files(t_element_list *elements);

int mx_ls(t_uls *uls);

void mx_delete_uls(t_uls *uls);

t_flags *mx_create_flags(void);

t_flags *mx_parse_flags(char *flag_string);

void mx_print_tab(int len, int max_name_size);

void mx_output_default(t_element_list *elements);

void mx_output(t_uls *uls, t_element_list *elements);

void mx_output_dirs(t_uls *uls);

t_element_list *mx_parse_elements(int argc, char **argv);

void mx_output_errors(t_element_list *element);

void mx_output_l(t_element_list *elements, bool print_total);

void mx_print_line_l(t_element *el, t_max_len_limits *len);

void mx_output_files(t_uls *uls, t_element_list *elements);

void mx_print_char_err(char c);

void mx_join_path(char **res, char *s2);

void mx_sort_elements(t_element_list **list);

int mx_get_int_length(int number);

#endif
