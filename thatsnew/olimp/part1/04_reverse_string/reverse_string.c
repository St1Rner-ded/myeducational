//Дана строка. Выведите её символы в обратном порядке.
//1 <= кол-во символов <= 1000
//По изначальному условию, предложение должно быть на русском, но в рамках тренировки я делаю всё на английском

#include <stdio.h>

size_t strlength(char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    char string[1001];
    printf ("\nEnter your sentence: ");
    while (1) {
        if (fgets (string, sizeof (string), stdin) == NULL) {
            printf ("\nNo input. Exit.\n");
            return 1;
        }
        if (string[strlength (string) - 1] != '\n') {
            int c;
            while ((c = getchar ()) != '\n' && c != EOF) {
                ;
            }
        }
        size_t len = strlength (string);
        if (len > 0 && string[len - 1] == '\n') {
            string[len - 1] = '\0';
            len = strlength (string);
        }
        if (len == 0) {
            printf ("Empty string. Try again: ");
            continue;
        }
        break;
    }
    printf ("Your sentence: %s\n", string);
    size_t len = strlength (string);
    printf ("Number of symbols in your sentence: %zu\n", len);
    char rev_string[1001];
    for (size_t i = 0; i < len; ++i) {
        rev_string [i] = string [len - 1 - i];
    }
    rev_string [len] = '\0';
    printf ("Your reversed sentence: %s\n", rev_string);
    return 0;
}