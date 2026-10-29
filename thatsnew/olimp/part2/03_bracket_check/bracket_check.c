//Дана строка из символов «(», «)», «[», «]», «{», «}». 
//Определите, является ли последовательность скобок правильной (каждой открывающей скобке соответствует закрывающая того же типа в правильном порядке).
//1 <= кол-во символов <= 1000

#include <stdio.h>
#include <stdlib.h>

typedef struct stackChar {
    char *data;
    size_t top;
    size_t capacity;
} stackChar;

void stackInit (stackChar *s, size_t init_capacity) {
    s->data = malloc (init_capacity * sizeof (char));
    if (!s->data) {
        perror ("Critical failure: initial memory didn't allocate.");
        exit (EXIT_FAILURE);
    }
    s->top = 0;
    s->capacity = init_capacity;
}

short stack_push (stackChar *s, char ch) {
    if (s->top >= s->capacity) {
        size_t new_capacity = s->capacity * 2;
        char *new_data = realloc (s->data, new_capacity * sizeof (char));
        if (!new_data) return 0;
        s->data = new_data;
        s->capacity = new_capacity;
    }
    s->data[s->top++] = ch;
    return 1;
}

short stack_pop (stackChar *s, char *out_ch) {
    if (s->top == 0) return 0;
    *out_ch = s->data[--s->top];
    return 1;
}

short stack_top (const stackChar *s, char *out_ch) {
    if (s->top == 0) return 0;
    *out_ch = s->data[s->top-1];
    return 1;
}

void stack_free (stackChar *s) {
    free (s->data);
    s->data = NULL;
    s->top = 0;
    s->capacity = 0;
}

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    char sequence [1001];
    printf ("Enter your string of brackets (openers and closers must have equal count): ");
        while (1) {
            if (fgets (sequence, sizeof (sequence), stdin) == NULL) {
                printf ("\nNo input. Exit.\n");
                return 1;
            }
            if (sequence[strlength (sequence) - 1] != '\n') {
                int c;
                while ((c = getchar ()) != '\n' && c != EOF) {
                    ;
                }
            }
            size_t len = strlength (sequence);
            if (len > 0 && sequence[len - 1] == '\n') {
                sequence[len - 1] = '\0';
                len = strlength (sequence);
            }
            if (len == 0) {
                printf ("Empty string. Try again: ");
                continue;
            }
            break;
        }
    char *p = sequence;
    stackChar stack;
    stackInit (&stack, 16);
    short is_wrong = 0;
    while (*p) {
        char ch = *p;
        if (ch == '(' || ch == '[' || ch == '{') {
            stack_push (&stack, ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            char top_ch;
            if (stack_top (&stack, &top_ch) == 0 || !(top_ch == ch - 1 || top_ch == ch - 2)) {
                is_wrong = 1;
                break;
            }
            else {
                char discarded;
                stack_pop (&stack, &discarded);
            }
        }
        ++p;
    }
    char any_ch;
    if (is_wrong == 1 || 1 == stack_top (&stack, &any_ch)) {
        printf ("Your sequence is wrong.\n");
        stack_free (&stack);
        return 0;
    }    
    printf ("Your sequence is right.\n");
    stack_free (&stack);
    return 0;
}