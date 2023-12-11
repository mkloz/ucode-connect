#include "uls.h"

void mx_delete_element(t_element *el) {
	if (el == NULL) return;
	mx_strdel(&el->name);
	mx_strdel(&el->path);
	mx_strdel(&el->error_message);
	for (t_element_list *list = el->inner_elements; list; list = list->next) {
		mx_delete_element(list->data);
	}
	mx_clear_list((t_list **) &el->inner_elements);
	free(el);
	el = NULL;
}

void mx_output_errors(t_element_list *element) {
	mx_sort_elements(&element);

	for (t_element_list *error = element; error; error = error->next) {
		mx_printerr("uls: ");
		mx_printerr((error->data->name));
		mx_printerr(": ");
		mx_printerr(error->data->error_message);
		mx_printerr("\n");
	}
}

void mx_print_char_err(char c) {
	write(STDERR_FILENO, &c, 1);
}
