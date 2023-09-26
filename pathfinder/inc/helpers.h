#ifndef MKLOZ_HELPERS_H
#define MKLOZ_HELPERS_H

#include "base.h"

void mx_concat_lists(t_list **list1, t_list **list2);
t_list *mx_list_find_where(t_list *list, void *data, t_comp_func *is_equal);
void mx_clear_list(t_list **list);
#endif
