#include "../../inc/uls.h"

char **mx_exclude_hidden(char **arr, t_flags *opts) {
	char **res = NULL;
	char *str = NULL;
	int len = 0;
	int i = 0;

	for (; arr[len] != NULL; len++);

	if (opts->A) i = 2;

	for (; i < len; i++) {
		if (arr[i][0] == '.' && !opts->a && !opts->A) {
			continue;
		}
		str = mx_strjoin(str, arr[i]);
		str = mx_strjoin(str, " ");
	}

	res = mx_strsplit(str, ' ');
	free(str);
	mx_del_strarr(&arr);

	return res;
}

