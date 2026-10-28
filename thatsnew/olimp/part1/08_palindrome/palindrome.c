//Дана строка. Определите, является ли она палиндромом — то есть читается ли одинаково слева направо и справа налево.
//1 <= кол-во символов <= 1000

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

void string_redacting (const char *string, char *redacted) {
    const char *p = string;
    size_t q = 0;
    for (;*p;++p) {
        char c = *p;
        if (c > 64 && c < 91) c += 32;
        if (c > 96 && c < 123) redacted [q++] = c;
    }
    redacted[q] = '\0';
}

int is_palindrome (const char *redacted, const size_t len) {
    if (len < 2) return 1;
    size_t i = 0, j = len - 1;
    while (i < j) {
        if (redacted[i] != redacted[j]) {
            return 0;
        }
        ++i;
        --j;
    }
    return 1;
}

int main (void) {
    char string[1001];
    printf ("\nEnter your sentence: ");
    while (1) {
        if (fgets (string, sizeof (string), stdin) == NULL) {
            printf ("\nNo input. Exit.\n");
            return 1;
        }
        if (string[strlength (string) - 1] != '\n') {
            int c;
            while ((c = getchar ()) != '\n' && c != EOF) {
                ;
            }
        }
        size_t len = strlength (string);
        if (len > 0 && string[len - 1] == '\n') {
            string[len - 1] = '\0';
            len = strlength (string);
        }
        if (len == 0) {
            printf ("Empty string. Try again: ");
            continue;
        }
        break;
    }
    printf ("Your sentence: %s\n", string);
    size_t len = strlength (string);
    printf ("Number of symbols in your sentence: %zu\n", len);
    char redacted [1001];
    string_redacting (string, redacted);
    size_t red_len = strlength (redacted);
    int condition = is_palindrome (redacted, red_len);
    printf ((condition == 1) ? "Your string is palindrome\n\n" : "Your string is not palindrome\n\n");
    return 0;
}