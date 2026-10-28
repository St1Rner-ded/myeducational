//Даны три целых числа. Найдите наибольшее из них.
//-(10^9) <= значения <= 10^9

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int max(const int a, const int b, const int c) {
    return (a >= b && a >= c) ? a : (b >= c) ? b : c;
}

int main (void) {
    int array[3];
    char line[32];
    printf ("Enter three numbers:\n");
    for (size_t i = 0; i < 3; ++i) {
        int n = 0;
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
            if (sscanf (line, "%d", &n) != 1) {
                printf ("You didn't enter a number. Try again: ");
                continue;
            }
            if (n < -1000000000 || n > 1000000000) {
                printf ("Your number is too low or too big. Try again: ");
                continue;
            }
            break;
        }
        array[i] = n;
    }
    printf("Max value is: %d\n", max (array[0], array[1], array[2]));
    return 0;
}