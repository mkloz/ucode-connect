#include "helpers.h"

t_list *mx_list_find_where(t_list *list, void *data, t_comp_func is_equal) {
    t_list *current = list;

    while (current != NULL) {
        if (is_equal(current->data, data)) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void mx_concat_lists(t_list **list1, t_list **list2) {
    if (list1 == NULL || list2 == NULL) return;

    if (*list1 == NULL) {
        *list1 = *list2;
        *list2 = NULL;
        return;
    }

    t_list *current = *list1;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = *list2;
    *list2 = NULL;
}

void mx_clear_list(t_list **list) {
    if (*list == NULL
        || list == NULL) {
        return;
    }

    while (*list != NULL) {
        t_list *temp = (*list)->next;
        free(*list);
        *list = temp;
    }

    list = NULL;
}
