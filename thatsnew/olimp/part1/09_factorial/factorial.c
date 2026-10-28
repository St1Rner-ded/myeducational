//Дано целое число от 0 до 20. Нужно вычислить факториал этого числа.

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
    size_t factorial = 1;
    printf ("\nEnter number from 0 to 20: ");
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
        if (n > 20) {
            printf ("Your number is too big. Try again: ");
            continue;
        }
        break;
    }
    for (unsigned i = 1;i <= n; ++i) {
        factorial *= i;
    }
    printf ("\n%zu! = %zu\n\n", n, factorial);
    return 0;
}