// ============================================================
//  M2-T1 · Сколько единиц в числе (popcount)
//  Куда сдать: solutions/M2/M2-T1.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined M2-T1.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: две реализации одной функции — посчитать число единичных битов.
//
//  count_ones_v1(n) — «в лоб»: сдвигай вправо и смотри на младший бит,
//                     ровно 32 итерации (или 64 — подумай, от чего зависит).
//  count_ones_v2(n) — трюк: повторяй `n = n & (n - 1)`, пока n не станет нулём.
//                     Итераций будет ровно столько, сколько единиц.
//
//  ОБЯЗАТЕЛЬНО: параметр типа `unsigned` (не `int`!). Почему — вопрос 2.
//
//  ВОПРОСЫ ДЛЯ ОТЧЁТА (ответы пиши в solutions/notes/M2.md):
//   1) Что именно делает выражение `n & (n - 1)` и почему оно сбрасывает
//      ровно один младший единичный бит? Разбери на примере n = 0b1100.
//   2) Почему параметр `unsigned`, а не `int`? Что произойдёт при
//      `(-8) >> 1` и почему это зависит от компилятора?
//   3) Чем `n >> 1` отличается от `n / 2` для отрицательных n?
//   4) Сколько итераций сделает v1 и v2 для n = 1 и для n = 0xFFFFFFFF?
// ============================================================
#include <cstdint>
#include <cstdio>

int count_ones_v1(unsigned n) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)n;
    return 0;
    // >>> SOLUTION END
}

int count_ones_v2(unsigned n) {
    // >>> SOLUTION2 START (меняй только здесь)
    // TODO: твой код
    (void)n;
    return 0;
    // >>> SOLUTION2 END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void check(unsigned n, int want) {
    const int g1 = count_ones_v1(n);
    const int g2 = count_ones_v2(n);
    if (g1 != want) { std::printf("FAIL v1 n=0x%X: got %d, want %d\n", n, g1, want); ++g_fail; }
    if (g2 != want) { std::printf("FAIL v2 n=0x%X: got %d, want %d\n", n, g2, want); ++g_fail; }
}
int main() {
    check(0u, 0);
    check(1u, 1);
    check(2u, 1);
    check(3u, 2);
    check(0xAu, 2);            // 1010
    check(0xFFu, 8);
    check(0xAAu, 4);           // 10101010
    check(12345u, 6);
    check(0x80000000u, 1);     // только старший бит
    check(0xFFFFFFFFu, 32);    // все биты
    check(0xDEADBEEFu, 24);
    check(0x0F0F0F0Fu, 16);
    if (sizeof(unsigned) != 4) std::printf("ВНИМАНИЕ: sizeof(unsigned) = %zu, тесты рассчитаны на 4\n",
                                           sizeof(unsigned));
    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
