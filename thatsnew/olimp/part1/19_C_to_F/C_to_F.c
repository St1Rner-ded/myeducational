//Дана температура C в градусах Цельсия. Переведите её в градусы Фаренгейта по формуле F = C × 9/5 + 32.
//-273 <= C <= 1000

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    int celcius = 0;
    char line[6];
    printf ("Enter temperature in Celcius: ");
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
        if (sscanf (line, "%d", &celcius) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (celcius < -273 || celcius > 1000) {
            printf ("Your number is too low or too big. Try again: ");
            continue;
        }
        break;
    }
    printf ("\nTemperature in Fahrenhite: %d\n", celcius * 9/5 + 32);
    return 0;
}