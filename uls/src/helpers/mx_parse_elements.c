#include "../../inc/uls.h"

void mx_parse_elements(char **elements, int n, char ***directories, char ***files) {
	struct stat st;
	char *str_files = NULL;
	char *str_dirs = NULL;

	for (int i = 0; i < n; i++) {
		if (lstat(elements[i], &st) < 0) {
			char *mx_err = "uls: ";
			mx_err = mx_strjoin(mx_err, elements[i]);
			perror(mx_err);
			free(mx_err);
			continue;
		}

		if (S_ISLNK(st.st_mode)) {
			str_files = mx_strjoin(str_files, elements[i]);
			str_files = mx_strjoin(str_files, " ");
		} else if (!S_ISDIR(st.st_mode)) {
			str_files = mx_strjoin(str_files, elements[i]);
			str_files = mx_strjoin(str_files, " ");
		} else {
			str_dirs = mx_strjoin(str_dirs, elements[i]);
			str_dirs = mx_strjoin(str_dirs, " ");
		}
	}

	if (str_files != NULL) {
		*files = mx_strsplit(str_files, ' ');
		free(str_files);
	}

	if (str_dirs != NULL) {
		*directories = mx_strsplit(str_dirs, ' ');
		free(str_dirs);
	}
}

