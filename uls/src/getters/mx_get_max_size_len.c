#include "../../inc/uls.h"

int mx_get_max_size_len(char **files, int *links_max_amount_len, char *dir_path) {
	struct stat buf;
	int max_size = 0;
	int max_links_len = 0;

	for (int i = 0; files[i] != NULL; i++) {
		char *path = mx_strjoin(dir_path, files[i]);

		lstat(path, &buf);
		free(path);
		if (buf.st_size > max_size) {
			max_size = buf.st_size;
		}
		if (buf.st_nlink > max_links_len) {
			max_links_len = buf.st_nlink;
		}
	}
	*links_max_amount_len = mx_strlen(mx_itoa(max_links_len));

	return mx_strlen(mx_itoa(max_size));
}
