#include "uls.h"

int main(int argc, char *argv[]) {
	int args_elements_index = 1;
	int exit_code = EXIT_SUCCESS;
	t_flags *flags = mx_get_flags(argv, &args_elements_index);
	t_element **args = mx_get_names(argc, argv, args_elements_index);

	mx_sort_elements(&args, flags);

	if (args) {
		mx_dir(&args, flags);
	}
	if (flags->ex) {
		exit_code = EXIT_FAILURE;
	}

	free(flags);
	flags = NULL;
	return exit_code;
}
