//Задача: определить, является ли строка палиндромом.

#include <stdio.h>
#include <stdlib.h>

size_t strlength(const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

char* is_palindrome(const char* string, const size_t len) {
    char* redacted_string = malloc(len + 1);
    
}

int main (void) {
    char string[1001];
    printf ("\nEnter your sentence: ");
    fgets (string, sizeof(string), stdin);
    printf ("Your sentence: %s\n", string);
    size_t len = strlength (string);
    if (len > 0) {
        string[len - 1] = (string[len - 1] == '\n') ? '\0' : string[len - 1];
        len = strlength(string);
    }
    printf ("Number of symbbols in your sentence: %zu\n", len);   
    printf ("%s", is_palindrome(string, len));
    return 0;
}