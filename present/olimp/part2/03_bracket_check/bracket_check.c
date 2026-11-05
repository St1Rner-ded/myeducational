//Дана строка из символов «(», «)», «[», «]», «{», «}».
//Определите, является ли последовательность скобок правильной (каждой открывающей скобке соответствует закрывающая того же типа в правильном порядке).
//1 <= кол-во символов <= 1000

#include <stdio.h>

#define MAX_L 1000

static int is_bracket (char ch) {
    return ch == '(' || ch == ')' ||
           ch == '[' || ch == ']' ||
           ch == '{' || ch == '}';
}

static int is_opener (char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

static int is_closer (char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

static int matches (char opener, char closer) {
    return
    (opener == '(' && closer == ')') ||
    (opener == '[' && closer == ']') ||
    (opener == '{' && closer == '}');
}

static int read_sequence (char *sequence) {
    if (scanf("%1000s", sequence) != 1) {
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
    if (sequence[0] == '\0') return 0;
    for (const char *p = sequence; *p; ++p) {
        if (!is_bracket(*p)) {
            return 0;
        }
    }
    return 1;
}

int main (void) {
    char sequence [MAX_L + 1];
    if (!read_sequence(sequence)) return 1;
    char stack [MAX_L];
    int top = 0;
    int wrong = 0;
    for (int i = 0; sequence [i]; ++i) {
        char ch = sequence[i];
        if (is_opener (ch)) {
            if (top >= MAX_L) {
                wrong = 1;
                break;
            }
            stack[top] = ch;
            ++top;
        }
        else if (is_closer(ch)) {
            if (top == 0 || !matches(stack[top - 1], ch)) {
                wrong = 1;
                break;
            }
            --top;
        }
        else {
            wrong = 1;
            break;
        }
    }
    if (!wrong && top) {
        wrong = 1;
    }
    if (wrong) {
        printf("Your sequence is wrong.\n");
    }
    else {
        printf("Your sequence is right.\n");
    }
    return 0;
}