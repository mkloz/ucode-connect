#include "uls.h"

static void swap_elements(t_element **one, t_element **two) {
	t_element *temp = *one;

	*one = *two;
	*two = temp;
}

void mx_sort_elements(t_element_list **list) {
	bool swapped = true;
	t_element_list *ptr1 = NULL;
	t_element_list *lptr = NULL;

	if (*list == NULL)
		return;

	while (swapped) {
		swapped = false;
		ptr1 = *list;

		while (ptr1->next != lptr) {
			if (ptr1->data->error_message != NULL) {
				if (mx_strcmp(ptr1->data->name, ptr1->next->data->name) == 1) {
					swap_elements(&ptr1->data, &ptr1->next->data);
					swapped = true;
				}
			} else if (mx_strcmp(ptr1->data->name, ptr1->next->data->name) > 0) {
				swap_elements(&ptr1->data, &ptr1->next->data);
				swapped = true;
			}

			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
