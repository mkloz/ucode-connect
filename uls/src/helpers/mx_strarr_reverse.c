#include "../../inc/uls.h"

void mx_strarr_reverse(char **arr) {
	int len = 0;
	for (; arr[len] != NULL; ++len);
	len -= 2;

	for (int i = 0; i < len; i++) {
		char *temp = arr[i];
		arr[i] = arr[len];
		arr[len] = temp;
	}
}
