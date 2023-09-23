#include <stdbool.h>

void mx_sort_arr_int(int *arr, int size);

void mx_sort_arr_int(int *arr, int size) {
    bool again = false;

    for (int i = 0; i < size - 1; ++i) {
        if (arr[i] <= arr[i + 1]) {
            continue;
        }
        int temp = arr[i + 1];

        arr[i + 1] = arr[i];
        arr[i] = temp;
        again = true;
    }

    if (again) {
        mx_sort_arr_int(arr, size);
    }
}
