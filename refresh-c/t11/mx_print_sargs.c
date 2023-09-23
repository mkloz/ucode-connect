#include <stdbool.h>

int mx_strcmp(const char *s1, const char *s2);
void mx_printstr(const char *s);
void mx_printchar(char c);
static void sort_arr(char *arr[], int size);

static void sort_arr(char *arr[], int size) {
    bool again = false;

    for (int i = 0; i < size - 1; ++i) {
        if (mx_strcmp(arr[i], arr[i + 1]) < 0) {
            continue;
        }
        char *temp = arr[i + 1];

        arr[i + 1] = arr[i];
        arr[i] = temp;
        again = true;
    }

    if (again) {
        sort_arr(arr, size);
    }
}

int main(int argc, char *argv[]) {
    sort_arr(++argv, --argc);

    for (int i = 0; i < argc; ++i) {
        mx_printstr(argv[i]);
        mx_printchar('\n');
    }

    return 0;
}

