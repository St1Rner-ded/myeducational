//Дано число N. Выведите таблицу умножения числа N на числа от 1 до 10.
//1 <= N <= 100

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
    printf ("Enter your number from 1 to 100: ");
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
            if (number == 0 || number > 100) {
                printf ("Your number is 0 or too big. Try again: ");
                continue;
            }
            break;
        }
    for (unsigned i = 1; i <= 10; ++i) {
        printf ("%u * %u\t= %u\n", number, i, number * i);
    }
    return 0;
}