//Даны два натуральных числа. Найдите их наибольший общий делитель.
//1 ≤ значения ≤ 10^9

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    unsigned numbers[2];
    char line[32];
    printf ("\nEnter two numbers from 1 to 1000000000:\n\n");
    for (size_t i = 0; i < 2; ++i) {
        unsigned n = 0;
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
            if (n == 0 || n > 1000000000) {
                printf ("Your number is 0 or too big. Try again: ");
                continue;
            }
            break;
        }
        numbers[i] = n;
    }
    if (numbers[1] > numbers[0]) {
        unsigned temp_num = numbers[0];
        numbers[0] = numbers[1];
        numbers[1] = temp_num;
    }
    while (numbers[0] % numbers[1] != 0) {
        unsigned modulo = numbers[0] % numbers[1];
        numbers[0] = numbers[1];
        numbers[1] = modulo;
    }
    printf ("The biggest common divider of your numbers is %u\n\n", numbers[1]);
    return 0;
}