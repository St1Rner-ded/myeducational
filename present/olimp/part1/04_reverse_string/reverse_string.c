//Дана строка. Выведите её символы в обратном порядке.
//1 <= кол-во символов <= 1000
//По изначальному условию, предложение должно быть на русском, но в рамках тренировки я делаю всё на английском

#include <stdio.h>

#define MAX_L 1000

static int read_string (char *string) {
    if (scanf("%1000s", string) != 1) {
        return 0;
    }
    int bad = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ' && c != '\t' && c != '\r') {
            bad = 1;
        }
    }
    if (bad) return 0;
    if (string[0] == '\0') return 0;
    return 1;
}

int main (void) {
    char string[MAX_L + 1];
    if (!read_string (string)) return 1;
    int len = 0;
    while (string[len] != '\0' && len < MAX_L) {
        len++;
    }
    char rev[MAX_L + 1];
    for (int i = 0; string[i] != '\0'; i++) {
        rev[i] = string[len-1-i];
    }
    rev[len] = '\0';
    for (int i = 0; rev[i] != '\0'; ++i) {
        printf ("%c", rev[i]);
    }
    return 0;
}