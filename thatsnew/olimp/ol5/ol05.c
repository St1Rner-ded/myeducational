#include <stdio.h>

char to_lower_ascii (char ch) {
    return ('A' <= ch && ch <= 'Z') ? ch+32 : ch;
}

int main (void) {
    char string [1001];
    printf ("Enter your string: ");
    fgets (string, sizeof(string), stdin);
    unsigned vowel_letters = 0;
    size_t i = 0;
    while (string[i] != '\0') {
        char low_key = to_lower_ascii(string[i]);
        if (low_key == 'a' || low_key == 'e' || low_key == 'i' || low_key == 'o' || low_key == 'u' || low_key == 'y') {
            vowel_letters++;
        }
        i++;
    }
    printf ("Your string has [%u] vowel letters.\n", vowel_letters);
    return 0;
}