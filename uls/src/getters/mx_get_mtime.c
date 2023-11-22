#include "../../inc/uls.h"

char *mx_get_mtime(char *ntime) {
	char *res = mx_strnew(12);
	res = mx_strncpy(res, ntime + 4, 12);
	time_t seconds = time(NULL);
	char *cur_time = ctime(&seconds);

	if (mx_atoi(ntime + 20) < mx_atoi(cur_time + 20)) {
		mx_strncpy(res + 7, ntime + 19, 5);
	}
	return res;
}
