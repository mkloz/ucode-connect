#include "../../inc/uls.h"

int mx_get_col(char **el, int n, int ws_col) {
	int max_len = 0;

	for (int i = 0; i < n; i++) {
		if (mx_strlen(el[i]) > max_len)
			max_len = mx_strlen(el[i]);
	}

	int min = n;
	int sum = 0;
	int tmp = 0;
	for (int i = 0; i < n; i++) {
		sum += mx_strlen(el[i]);
		if (mx_strlen(el[i]) < max_len) {
			sum += (max_len - mx_strlen(el[i]));
		}

		if (sum >= ws_col && tmp < min) {
			min = tmp;
			tmp = 0;
			sum = 0;
			continue;
		}
		sum += '\t';
		tmp++;
	}
	return min;
}

