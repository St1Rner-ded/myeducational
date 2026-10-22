#include <stdio.h>

size_t strlength(char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    char string[1001];
    printf ("\nEnter tour sentence: ");
    fgets (string, sizeof(string), stdin);
    printf ("Your sentence: %s\n", string);
    size_t len = strlength (string);
    if (len > 0) {
        string[len - 1] = (string [len - 1] == '\n') ? '\0' : string[len - 1];
        len = strlength(string);
    }
    printf ("Number of symbbols in your sentence: %zu\n", len);
    char rev_string[1001];
    for (size_t i = 0; i < len; ++i) {
        rev_string [i] = string [len - 1 - i];
    }
    rev_string [len] = '\0';
    printf ("Your reversed sentence: %s\n", rev_string);
    return 0;
}