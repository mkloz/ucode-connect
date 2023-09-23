#include "../inc/list.h"

t_list *mx_create_node(void *data) {
    t_list *list = malloc(sizeof(t_list));
    list->data = data;
    list->next = NULL;

    return list;
}

int mx_list_size(t_list *list) {
    if (list == NULL)
        return 0;

    t_list *l = list;
    int len = 0;

    while (l != NULL) {
        l = l->next;
        len++;
    }

    return len;
}

void mx_push_front(t_list **list, void *data) {
    if (*list == NULL || list == NULL) {
        *list = mx_create_node(data);
        return;
    }

    t_list *l = mx_create_node(data);

    l->next = *list;
    *list = l;
}

void mx_push_back(t_list **list, void *data) {
    if (*list == NULL || list == NULL) {
        *list = mx_create_node(data);
        return;
    }

    t_list *l = *list;

    while (l->next != NULL) {
        l = l->next;
    }

    l->next = mx_create_node(data);
}

void mx_pop_front(t_list **list) {
    if (*list == NULL || list == NULL) {
        return;
    }

    t_list *l = (*list)->next;

    free(*list);
    *list = l;
}

void mx_pop_back(t_list **list) {
    if (*list == NULL || list == NULL) {
        return;
    }

    t_list *l = *list;

    while (l->next->next != NULL) {
        l = l->next;
    }

    free(l->next);
    l->next = NULL;
}

void mx_clear_list(t_list **list) {
    if (*list == NULL
        || list == NULL) {
        return;
    }

    while (*list != NULL) {
        t_list *temp = (*list)->next;
        free((*list)->data);
        free(*list);
        *list = temp;
    }

    list = NULL;
}

void mx_foreach_list(t_list *list, void (*f)(t_list *node)) {
    if (list == NULL || f == NULL) {
        return;
    }

    t_list *l = list;

    while (l != NULL) {
        f(l);
        l = l->next;
    }
}

void mx_foreach(t_list *list, void (*f)(void *)) {
    if (list == NULL || f == NULL) {
        return;
    }

    t_list *l = list;

    while (l != NULL) {
        f(l->data);
        l = l->next;
    }
}

void mx_del_node_if(t_list **list, bool (*cmp)(void *)) {
    if (list == NULL
        || (*list) == NULL
        || (*list)->data == NULL
        || cmp == NULL) {
        return;
    }

    t_list *l = *list;

    while (l->next != NULL) {
        if (cmp(l->next->data)) {
            t_list *t = l->next->next;
            free(l->next->data);
            free(l->next);
            l->next = t;

        }
        if (l->next != NULL)
            l = l->next;
    }

    if (cmp((*list)->data)) {
        t_list *temp = *list;

        *list = (*list)->next;
        free(temp->data);
        free(temp);
    }
}
