#include "../../inc/uls.h"

void mx_set_color(struct stat *buf) {
	if (S_ISDIR(buf->st_mode))
		mx_printstr(MX_COLOR_BLU);
	else if (S_ISFIFO(buf->st_mode))
		mx_printstr(MX_COLOR_BRN);
	else if (S_ISLNK(buf->st_mode))
		mx_printstr(MX_COLOR_MAG);
	else if (S_ISBLK(buf->st_mode))
		mx_printstr(MX_COLOR_BLU);
	else if (S_ISCHR(buf->st_mode))
		mx_printstr(MX_COLOR_BLU);
	else if ((buf->st_mode & S_IFMT) == S_IFSOCK)
		mx_printstr(MX_COLOR_GRN);
	else if (buf->st_mode & S_IEXEC)
		mx_printstr(MX_COLOR_RED);
	else if (S_ISREG(buf->st_mode))
		mx_printstr(MX_COLOR_NRM);
}
