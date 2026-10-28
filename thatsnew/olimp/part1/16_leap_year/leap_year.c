//Дан год N. Определите, является ли он високосным (делится на 4, но не на 100, либо делится на 400).
//1 <= N <= 9999

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int is_year_leap (const unsigned year) {
    if (year % 400 == 0) return 1;
    else if (year % 4 == 0 && year % 100 != 0) return 1;
    else return 0;
}

int main (void) {
    printf ("\nEnter a year:\n\n");
    unsigned year = 0;
    char line[32];
    while (1) {
        if (fgets (line, sizeof (line), stdin) == NULL) {
            printf ("\nYou entered an emptiness. Exit.\n");
            return 1;
        }
        if (line[strlength (line) - 1] != '\n') {
            int c;
            while ((c = getchar ()) != '\n' && c != EOF) {
                ;
            }
        }
        if (sscanf (line, "%u", &year) != 1) {
            printf ("You didn't enter a year. Try again: ");
            continue;
        }
        if (year == 0 || year > 9999) {
            printf ("Your year is 0 or too big. Try again: ");
            continue;
        }
        break;
    }
    printf ((is_year_leap(year) == 1) ? "\nYour year is leap.\n\n" : "\nYour year is common.\n\n");
    return 0;
}