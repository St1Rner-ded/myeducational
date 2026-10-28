//Дана строка и символ. Посчитайте, сколько раз символ встречается в строке.
//1 <= кол-во символов <= 1000
//По изначальному условию, строка должна быть на русском, но в рамках тренировки я делаю всё на английском

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    char string[1001];
    unsigned number_of_symb = 0;
    printf ("Enter your string: ");
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
    printf ("Your string: %s\n\nEnter which symbol you're looking for: ", string);
    char line[8];
    if (fgets (line, sizeof (line), stdin) == NULL) {
        printf ("\nNo input. Exit.\n");
        return 1;
    }
    if (line[0] == '\n') {
        printf ("Empty line. Exit.\n");
        return 1;
    }
    char symb = line[0];
    char *p = string;
    for (; *p; ++p) {
        if (*p == symb) {
            ++number_of_symb;
        }
    }
    printf ("\nNumber of selected symbol in your string: %u\n", number_of_symb);
    return 0;
}