//Задача: определить, является ли строка палиндромом.

#include <stdio.h>

size_t strlength(char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int is_even (size_t len) {
    return len % 2 == 0;
}

//Деление на 2 округляет вниз, было 3, стало 1.

int main (void) {
    char string[1001];
    printf ("\nEnter tour sentence: ");
    fgets (string, sizeof(string), stdin);
    printf ("Your sentence: %s\n", string);
    size_t len = strlength (string);
    if (len > 0) {
        string[len - 1] = (string[len - 1] == '\n') ? '\0' : string[len - 1];
        len = strlength(string);
    }
    printf ("Number of symbbols in your sentence: %zu\n", len);
    switch (is_even(len)) {
        case 0:
            size_t middle_i = len / 2 + 1;
            for (size_t right_i = middle_i, left_i = middle_i; string[left_i] == string [right_i]; ++right_i, --left_i)
            printf("Your string is odd: [div by 2 = %zu]\n", len / 2);
            break;
        case 1:
            printf("Your string is even: [divided by 2 = %zu]\n", len / 2);
    }
    return 0;
}