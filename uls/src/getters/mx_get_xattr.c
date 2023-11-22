#include "../../inc/uls.h"

int mx_get_xattr(char *file) {
	char *l = mx_strnew(1024);
	int nbytes = listxattr(file, l, 1024, XATTR_SHOWCOMPRESSION);
	ssize_t size = 0;
	char *link = mx_strnew(1024);

	if (!nbytes) {
		size = readlink(file, link, 1024);
		if (size >= 0) {
			nbytes = listxattr(link, l, 1024, XATTR_SHOWCOMPRESSION);
		}
	}

	mx_strdel(&l);
	mx_strdel(&link);
	return nbytes;
}
