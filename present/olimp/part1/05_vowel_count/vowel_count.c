//Дана строка из строчных русских букв. Посчитайте количество гласных букв (а, е, ё, и, о, у, ы, э, ю, я).
//1 <= кол-во символов <= 1000
//Вообще, по условию, предложение должно быть на русском, но в рамках тренировки я провожу всё на английском (a, e, i, o, u)

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

static char to_lower_ascii (char ch) {
    return ('A' <= ch && ch <= 'Z') ? ch+32 : ch;
}

static int checkvow (char ch) {
    char low_ch = to_lower_ascii(ch);
    return
    low_ch == 'a' ||
    low_ch == 'e' ||
    low_ch == 'i' ||
    low_ch == 'o' ||
    low_ch == 'u';
}

int main (void) {
    char string [MAX_L + 1];
    if (!read_string (string)) return 1;
    int vowels = 0;
    char *p = string;
    while (*p != '\0') {
        if (checkvow(*p)) vowels++;
        p++;
    }
    printf("%d", vowels);
    return 0;
}