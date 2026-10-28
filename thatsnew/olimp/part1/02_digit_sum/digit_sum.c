//Дано натуральное число N. Найдите сумму его цифр.
//1 <= N <= 10^18

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    size_t n = 0;
    char line[64];
    size_t sum = 0;
    printf ("Enter your number: ");
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
        if (sscanf (line, "%zu", &n) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (n == 0 || n > 1000000000000000000) {
            printf ("Your number is 0 or too big. Try again: ");
            continue;
        }
        break;
    }
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    printf ("Sum of digits: %zu\n", sum);
    return 0;
}