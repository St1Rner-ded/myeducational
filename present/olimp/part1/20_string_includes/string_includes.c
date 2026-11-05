//Дана строка и символ. Посчитайте, сколько раз символ встречается в строке.
//1 <= кол-во символов <= 1000
//По изначальному условию, строка должна быть на русском, но в рамках тренировки я делаю всё на английском

#include <stdio.h>

#define MAX_N 1000

int main (void) {
    char string[MAX_N + 1];
    char symb;
    unsigned number_of_symb = 0;
    if (fgets (string, sizeof (string), stdin) == NULL) {
        return 1;
    }
    if (scanf ("%c", &symb) != 1) {
        return 1;
    }
    char *p = string;
    for (; *p; ++p) {
        if (*p == symb) {
            ++number_of_symb;
        }
    }
    printf ("%u", number_of_symb);
    return 0;
}