#include "../../inc/uls.h"

char *mx_get_tabs(int rows, int col, int curr, char **files) {
	int max_len = mx_strlen(files[col]);
	int tmp_col = 0;
	char *tabs = (char *) malloc(2);
	tabs = NULL;

	for (int tmp = 0; tmp < rows - 1; tmp++) {
		tmp_col = col + tmp;

		if (files[tmp_col + 1] == NULL) {
			break;
		}

		int len1 = mx_strlen(files[tmp_col]);
		int len2 = mx_strlen(files[tmp_col + 1]);

		if (len1 != len2) {
			if (len1 > len2 && max_len < len1)
				max_len = len1;
			if (len1 < len2 && max_len < len2)
				max_len = len2;
		}
	}
	int len_curr = mx_strlen(files[curr]);

	if (len_curr < max_len) {
		while (len_curr != max_len) {
			tabs = mx_strjoin(tabs, " ");
			len_curr++;
		}
	}
	tabs = mx_strjoin(tabs, "\t");

	return tabs;
}

