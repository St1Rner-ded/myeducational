#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    unsigned n = 0;
    char line[32];
    printf ("Enter index of one of numbers of Fibonacci: ");
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
        if (sscanf (line, "%u", &n) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (n == 0 || n > 80) {
            printf ("Your index is 0 or too big. Try again: ");
            continue;
        }
        break;
    }
    size_t previous = 0, current = 0, next = 1;
    for (unsigned i = 0; i < n; ++i) {
        previous = current;
        current = next;
        next = previous + current;
    }
    printf ("Your number is: %zu\n", current);
    return 0;
}