//Дана строка, слова в которой разделены одним пробелом. Посчитайте количество слов.
//1 <= длина строки в символах <= 1000

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
    char last_symb = ' ';
    unsigned words_count = 0;
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
    if (*p != '\0') {
        for (;*p;++p) {
            if (*p != ' ' && last_symb == ' ') {
                ++words_count;
            }
            last_symb = *p;
        }
    }
    printf ("\nYour string contains %u word(s).\n\n", words_count);
    return 0;
}