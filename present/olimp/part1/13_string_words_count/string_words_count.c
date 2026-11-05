//Дана строка, слова в которой разделены одним пробелом. Посчитайте количество слов.
//1 <= длина строки в символах <= 1000

#include <stdio.h>

#define MAX_N 1000

int main (void) {
    char string [MAX_N + 1];
    char last_symb = ' ';
    unsigned words_count = 0;
    if (fgets (string, sizeof (string), stdin) == NULL) {
        return 1;
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
    printf ("%u\n", words_count);
    return 0;
}