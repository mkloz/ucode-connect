#include "../../inc/uls.h"

void mx_get_flags(int argc, char **argv, t_flags *opts) {
	int j = 0;
	for (int i = 1; i < argc; i++) {
		j = 1;
		if (argv[i][0] == '-') {
			while (argv[i][j] != '\0') {
				char c = argv[i][j];

				mx_check_flag(c, opts);
				j++;
			}
		}
	}
}

