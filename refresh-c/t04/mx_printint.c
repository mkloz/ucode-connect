#include <unistd.h>

#define INT_MIN (-__INT_MAX__ - 1)
#define INT_MIN_STRING "-2147483648"

void mx_printint(int n);
void mx_printchar(char c);

void mx_printint(int n) {
    if (n == 0) {
        mx_printchar('0');
        return;
    }

    if (n == INT_MIN) {
        write(STDOUT_FILENO, INT_MIN_STRING, 11);
        return;
    }

    if (n < 0) {
        mx_printchar('-');
        n = -n;
    }

    if (n / 10 != 0) {
        mx_printint(n / 10);
    }

    mx_printchar('0' + (n % 10));
}
