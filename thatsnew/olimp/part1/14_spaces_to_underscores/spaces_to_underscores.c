//Дана строка. Замените в ней все пробелы на символ подчёркивания.
//1 <= Кол-во символов в строке <= 1000

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    printf ("Enter your string:\n\n");
    char string [1001];
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
    char *p = string;
    for (;*p;++p) {
        if (*p == ' ') *p = '_';
    }
    printf ("\nYour new string: %s\n", string);
    return 0;
}