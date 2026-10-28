//Дано целое число N. Определите, чётное оно или нечётное.
//-1000000000 <= N <= 1000000000

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    int n = 0;
    char line[32];
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
    printf ("%s\n", (n % 2 == 0) ? "EVEN" : "ODD");
    return 0;
}