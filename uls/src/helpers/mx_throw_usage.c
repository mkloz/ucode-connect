#include "../../inc/uls.h"

void mx_throw_usage(void) {
	mx_printerr("usage: uls [-aAfGlmosp1rTtx] [file ...]\n");
	exit(EXIT_FAILURE);
}
