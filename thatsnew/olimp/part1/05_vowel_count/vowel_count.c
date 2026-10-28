//Дана строка из строчных русских букв. Посчитайте количество гласных букв (а, е, ё, и, о, у, ы, э, ю, я).
//1 <= кол-во символов <= 1000
//Вообще, по условию, предложение должно быть на русском, но в рамках тренировки я провожу всё на английском (a, e, i, o, u)

#include <stdio.h>

size_t strlength(char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

char to_lower_ascii (char ch) {
    return ('A' <= ch && ch <= 'Z') ? ch+32 : ch;
}

int main (void) {
    char string [1001];
    printf ("Enter your string: ");
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
    unsigned vowel_letters = 0;
    char *p = string;
    for (; *p; ++p) {
        char low_key = to_lower_ascii(*p);
        if (low_key == 'a' || low_key == 'e' || low_key == 'i' || low_key == 'o' || low_key == 'u') {
            vowel_letters++;
        }
    }
    switch (vowel_letters) {
        case 0:
            printf ("Your string doesn't have any vowel letters.\n");
            break;
        case 1:
            printf ("Your string has only one vowel letter\n");
            break;
        default:
            printf ("Your string has [%u] vowel letters.\n", vowel_letters);
    }
    return 0;
}