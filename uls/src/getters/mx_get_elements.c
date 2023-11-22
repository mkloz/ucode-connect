#include "../../inc/uls.h"

char **mx_get_elements(int argc, char **argv) {
	int counter = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			counter++;
		}
	}
	if (counter == 0) {
		return NULL;
	}

	char **res = (char **) malloc(counter + 1);
	int index = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			res[index] = mx_strdup(argv[i]);
			index++;
		}
	}
	res[index] = NULL;
	return res;
}

