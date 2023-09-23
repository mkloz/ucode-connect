#ifndef MKLOZ_LIST_H
#define MKLOZ_LIST_H

#include "stdlib.h"
#include "stdbool.h"

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

typedef struct s_zombie_list {
    t_list *list;
    int list_size;
    int zombie_count;
} t_zombie_list;

t_list *mx_create_node(void *data);
int mx_list_size(t_list *list);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **list);
void mx_pop_back(t_list **list);
void mx_clear_list(t_list **list);
void mx_foreach(t_list *list, void(*f)(void *));
void mx_foreach_list(t_list *list, void(*f)(t_list *node));
void mx_del_node_if(t_list **list, bool(*cmp)(void *));
#endif
