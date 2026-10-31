//Дан год N. Определите, является ли он високосным (делится на 4, но не на 100, либо делится на 400).
//1 <= N <= 9999

#include <stdio.h>

#define MAX_N 9999

static int is_year_leap (const unsigned year) {
    if (year % 400 == 0) return 1;
    else if (year % 4 == 0 && year % 100 != 0) return 1;
    else return 0;
}

int main (void) {
    unsigned year = 0;
    if (scanf("%u", &year) != 1 || year == 0 || year > MAX_N) {
        return 1;
    }
    printf ((is_year_leap(year) == 1) ? "YES" : "NO");
    return 0;
}