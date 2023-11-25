#include "uls.h"

static char *check_grp(t_element *total) {
    struct group *grp = NULL;
    char *name = NULL;
    
    grp = getgrgid(total->info.st_gid);
    if (grp) {
        name = mx_strdup(grp->gr_name);
        return name;
    }
    else {
        name = mx_itoa(total->info.st_gid);
        return name;
    }
}

static char *check_pw(t_element *total) {
    struct passwd *pw = NULL;
    char *name = NULL;

    pw = getpwuid(total->info.st_uid);
    if (pw) {
        name = mx_strdup(pw->pw_name);
        return name;
    }
    else {
        name = mx_itoa(total->info.st_uid);
        return name;    
    }
}

static void count_size(t_element_size *size, t_element *total) {
    char *name_grp = check_grp(total);
    char *name_pw = check_pw(total);

    if (size->lnk < total->info.st_nlink)
        size->lnk = total->info.st_nlink;
    if (size->size < total->info.st_size)
        size->size = total->info.st_size;
    if (size->group < mx_strlen(name_grp))
        size->group = mx_strlen(name_grp);
    if (size->usr < mx_strlen(name_pw))
        size->usr = mx_strlen(name_pw);
    free(name_grp);
    free(name_pw);
}

static void size_null(t_element_size *size) {
    size->lnk = 0;
    size->size = 0;
    size->group = 0;
    size->usr = 0;
}

static bool mx_check_device(t_element **names, t_element_size *size) {
    for (int i = 0; names[i]; i++) {
        if (IS_BLK(names[i]->info.st_mode) || IS_CHR(names[i]->info.st_mode)) {
            return size->is_dev = true;
        }
    }
    return size->is_dev = false;
}

void mx_delete_elements_list(t_element ***args, t_element **dirs) {
    t_element **del_arr = *args;

    for (int i = 0; del_arr[i]!= NULL; i++) {
        mx_strdel(&del_arr[i]->name);
        mx_strdel(&del_arr[i]->path);
        if (del_arr[i]->error_message)
            mx_strdel(&del_arr[i]->error_message);
        free(del_arr[i]);
        del_arr[i] = NULL;
    }
    free(*args);
    *args = dirs;
}

void mx_output_l(t_element **names, t_flags *fl, int flag) {
    t_element_size *size = malloc(sizeof(t_element_size));
    int blk_size = 0;
    int i = 0;

    size_null(size);
    for (i = 0; names[i]; i++) {
        blk_size += names[i]->info.st_blocks;
        count_size(size, names[i]);
    }
    if (flag == 1) {
        mx_printstr("total ");
        mx_printint(blk_size);
        mx_printchar('\n');
    }
    mx_check_device(names, size);
    for (i = 0; names[i]; i++)
        mx_print_all(names[i], size, fl);
    free(size);
}
