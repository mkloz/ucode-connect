#include "uls.h"

void mx_delete_uls(t_uls *uls) {
	for (t_element_list *el = uls->elements; el; el = el->next) {
		mx_delete_element(el->data);
	}
	mx_clear_list((t_list **) &uls->elements);
	mx_clear_list((t_list **) &uls->files);
	mx_clear_list((t_list **) &uls->dirs);
	mx_clear_list((t_list **) &uls->errors);

	free(uls->flags);
}

int main(int argc, char *argv[]) {
	t_flags *flags = mx_parse_flags(argc > 1 ? argv[1] : "-");
	t_element_list *elements = mx_parse_elements(argc, argv);

	mx_sort_elements(&elements);

	t_uls uls = {elements,
	             mx_get_files(elements),
	             mx_get_dirs(elements),
	             mx_get_errors(elements),
	             flags, EXIT_SUCCESS};
	int exit_code = mx_ls(&uls);

	mx_delete_uls(&uls);

	return exit_code;
}
