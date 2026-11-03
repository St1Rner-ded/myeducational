//Дан текст, слова в котором разделены одним пробелом.
//Найдите слово, которое встречается чаще всех.
//Гарантируется, что такое слово единственное.
//1 <= длина строки в символах <= 10000

#include <stdio.h>

#define MAX_N 10000
#define MAX_WORDS (MAX_N + 1) / 2

typedef struct {
    char *word;
    int count;
} WordEntry;

static int is_separator (const char ch) {
    return
    ch == ' ' ||
    ch == '\n';
}

int string_eq (const char *string_a, const char *string_b) {
    const char *p = string_a;
    const char *q = string_b;
    while (*p != '\0' || *q != '\0') {
        if (*p != *q) return 0;
        p++;
        q++;
    }
    return 1;
}

int main (void) {
    static char string [MAX_N + 1];
    static WordEntry entries [MAX_WORDS];
    int used = 0;
    char last_ch = ' ';
    if (fgets (string, sizeof (string), stdin) == NULL) {
        return 1;
    }
    char *p = string;
    char *start = p;
    for (; *p != '\0'; p++) {
        char ch = *p;
        if (!is_separator (ch) && is_separator (last_ch)) {
            start = p;
        }
        if (is_separator (ch) && !is_separator (last_ch)) {
            *p = '\0';
            int found = 0;
            for (int k = 0; k < used; k++) {
                if (string_eq (entries[k].word, start)) {
                    entries[k].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                entries[used].word = start;
                entries[used].count = 1;
                used++;
            }
        }
        last_ch = ch;
    }
    int max_count = 0;
    int neccessary = 0;
    for (int k = 0; k < used; k++) {
        if (entries[k].count > max_count) {
            max_count = entries[k].count;
            neccessary = k;
        }
    }
    printf ("%s", entries[neccessary].word);
    return 0;
}