//Дано натуральное число N. Определите, является ли оно простым.
//1 ≤ N ≤ 10^6

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int is_prime (const unsigned number) {
    if (number < 2) return 0;
    if (number % 2 == 0) {
        return (number == 2);
    }
    for (unsigned div = 3; div <= number / div; div += 2) {
        if (number % div == 0) return 0;
    }
    return 1;
}

int main (void) {
    unsigned number = 0;
    char line[32];
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
    printf ((is_prime (number) == 1) ? "\nYour number is prime.\n\n" : "\nYour number isn't prime.\n\n");
    return 0;
}