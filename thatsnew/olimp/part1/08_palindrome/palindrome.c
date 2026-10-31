//Дана строка. Определите, является ли она палиндромом — то есть читается ли одинаково слева направо и справа налево.
//1 <= кол-во символов <= 1000

#include <stdio.h>

#define MAX_L 1000

static int string_redacting (const char *string, char *redacted) {
    const char *p = string;
    int q = 0;
    for (;*p;++p) {
        char c = *p;
        if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
        if (c >= 'a' && c <= 'z') redacted [q++] = c;
    }
    redacted[q] = '\0';
    return q;
}

static int is_palindrome (const char *string, char *redacted) {
    int len = string_redacting (string, redacted);
    if (len < 2) return 1;
    int i = 0, j = len - 1;
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
    char string[MAX_L + 1];
    if (fgets (string, sizeof (string), stdin) == NULL) {
        return 1;
    }
    char redacted [MAX_L + 1];
    int condition = is_palindrome (string, redacted);
    printf ((condition == 1) ? "Your string is palindrome\n\n" : "Your string is not palindrome\n\n");
    return 0;
}