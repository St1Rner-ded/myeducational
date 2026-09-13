/* ============================================================
   L2-T1 · Своя стандартная библиотека
   Куда сдать: solutions/L2/L2-T1.c
   ============================================================ */
/*  Компиляция:  gcc -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L2-T1.c -o t && ./t */
/*  Ожидание:    ALL TESTS PASSED */
/*  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END. */
/*  ЗАДАЧА: реализовать три функции БЕЗ <string.h> (подключать его запрещено):
      void   swap_ints(int *a, int *b);               обмен значений
      size_t my_strlen(const char *s);                длина, не считая '\0'
      void   my_strcpy(char *dst, const char *src);   копирование вместе с '\0'
    ВОПРОСЫ ДЛЯ ОТЧЁТА:
      1) Почему swap_ints принимает указатели, а не значения?
      2) Что произойдёт при swap_ints(p, p) — один и тот же адрес дважды?
      3) Почему у my_strcpy параметр dst не const, а src — const?              */
#include <stddef.h>
#include <stdio.h>

void swap_ints(int *a, int *b) {
    /* >>> SOLUTION START (меняй только здесь) */
    /* TODO: твой код */
    (void)a; (void)b;
    /* >>> SOLUTION END */
}

size_t my_strlen(const char *s) {
    /* >>> SOLUTION2 START (меняй только здесь) */
    /* TODO: твой код */
    (void)s;
    return 0;
    /* >>> SOLUTION2 END */
}

void my_strcpy(char *dst, const char *src) {
    /* >>> SOLUTION3 START (меняй только здесь) */
    /* TODO: твой код */
    (void)dst; (void)src;
    /* >>> SOLUTION3 END */
}

/* -------------------- тесты: НЕ редактируй -------------------- */
static int g_fail = 0;
int main(void) {
    int x = 1, y = 2;
    swap_ints(&x, &y);
    if (!(x == 2 && y == 1)) { printf("FAIL swap_ints: x=%d y=%d\n", x, y); ++g_fail; }

    int z = 5;
    swap_ints(&z, &z);   /* один и тот же адрес — значение не должно потеряться */
    if (z != 5) { printf("FAIL swap_ints(&z,&z): z=%d, ожидалось 5\n", z); ++g_fail; }

    const char *strs[]  = {"", "a", "hello", "with space", "0", "C-style string!"};
    const size_t lens[] = {0,   1,   5,       10,           1,   15};
    for (size_t i = 0; i < sizeof strs / sizeof strs[0]; ++i) {
        const size_t got = my_strlen(strs[i]);
        if (got != lens[i]) {
            printf("FAIL my_strlen(\"%s\"): got %zu, want %zu\n", strs[i], got, lens[i]);
            ++g_fail;
        }
    }

    char buf[64];
    my_strcpy(buf, "copy me");
    if (buf[0] != 'c' || buf[7] != '\0') { printf("FAIL my_strcpy: buf=\"%s\"\n", buf); ++g_fail; }
    my_strcpy(buf, "");
    if (buf[0] != '\0') { printf("FAIL my_strcpy для пустой строки\n"); ++g_fail; }

    if (g_fail == 0) puts("ALL TESTS PASSED");
    else printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
