#define UPPER_CASE_ALPHABET_START 65
#define LOWER_CASE_ALPHABET_START 97
#define ALPHABET_LENGTH 26

void mx_printchar(char c);

void mx_print_alphabet(void) {
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        mx_printchar(i % 2 == 0 ? i + UPPER_CASE_ALPHABET_START
                                : i + LOWER_CASE_ALPHABET_START);
    }

    mx_printchar('\n');
}
