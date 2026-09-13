/* ============================================================
   L1-T1 · Разворот массива на месте
   Куда сдать: solutions/L1/L1-T1.c
   ============================================================ */
/*  Компиляция:  gcc -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L1-T1.c -o t && ./t */
/*  Ожидание:    ALL TESTS PASSED */
/*  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END. */
/*  ЗАДАЧА: reverse_array(a, n) разворачивает массив НА МЕСТЕ,
    без второго массива, за O(n). n == 0, n == 1 и a == NULL не должны ломаться.
    ВОПРОС ДЛЯ ОТЧЁТА: почему в C запись `int *a` и `int a[]` в параметрах
    функции — это одно и то же? Как функция вообще узнаёт длину массива?      */
#include <stddef.h>
#include <stdio.h>

void reverse_array(int *a, size_t n) {
    /* >>> SOLUTION START (меняй только здесь) */
    /* TODO: твой код */
    (void)a; (void)n;
    /* >>> SOLUTION END */
}

/* -------------------- тесты: НЕ редактируй -------------------- */
static int g_fail = 0;
static void check_arr(const int *got, const int *want, size_t n, const char *what) {
    for (size_t i = 0; i < n; ++i) {
        if (got[i] != want[i]) {
            printf("FAIL %s: элемент %zu = %d, ожидалось %d\n", what, i, got[i], want[i]);
            ++g_fail;
            return;
        }
    }
}
int main(void) {
    { int a[5] = {1, 2, 3, 4, 5}; const int w[5] = {5, 4, 3, 2, 1};
      reverse_array(a, 5); check_arr(a, w, 5, "{1..5}"); }
    { int a[4] = {1, 2, 3, 4}; const int w[4] = {4, 3, 2, 1};
      reverse_array(a, 4); check_arr(a, w, 4, "{1..4}"); }
    { int a[1] = {7}; const int w[1] = {7};
      reverse_array(a, 1); check_arr(a, w, 1, "{7}"); }
    { int a[2] = {1, 2}; const int w[2] = {2, 1};
      reverse_array(a, 2); check_arr(a, w, 2, "{1,2}"); }
    { int a[1] = {9}; const int w[1] = {9};
      reverse_array(a, 0); check_arr(a, w, 1, "n=0 (массив не тронут)"); }
    reverse_array(NULL, 0);   /* не должно падать */
    if (g_fail == 0) puts("ALL TESTS PASSED");
    else printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
