//Дана строка. Замените в ней все пробелы на символ подчёркивания.
//1 <= Кол-во символов в строке <= 1000

#include <stdio.h>

#define MAX_N 1000

int main (void) {
    char string [MAX_N + 1];
    if (fgets (string, sizeof (string), stdin) == NULL) {
        return 1;
    }
    char *p = string;
    for (;*p;++p) {
        if (*p == ' ') *p = '_';
    }
    printf ("%s", string);
    return 0;
}