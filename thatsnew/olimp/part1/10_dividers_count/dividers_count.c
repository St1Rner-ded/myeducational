//Дано натуральное число N. Найдите количество его натуральных делителей (включая 1 и само N)
//1 <= N <= 10^6

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    unsigned number = 0;
    char line[32];
    unsigned divs_count = 1;
    printf ("\nEnter your number from 1 to 1000000: ");
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
        if (sscanf (line, "%u", &number) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (number == 0 || number > 1000000) {
            printf ("Your number is 0 or too big. Try again: ");
            continue;
        }
        break;
    }
    for (unsigned i = number - 1; i > 0; --i) {
        if (number % i == 0) ++divs_count;
    }
    printf ("\nNumber of dividers of your number is: %u\n\n", divs_count);
    return 0;
}