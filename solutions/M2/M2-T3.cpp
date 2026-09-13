// ============================================================
//  M2-T3 · Арифметика без переполнения (saturating)
//  Куда сдать: solutions/M2/M2-T3.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined M2-T3.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА:
//    int32_t  sat_add(int32_t a, int32_t b) — сложение с насыщением:
//             если результат больше INT32_MAX -> INT32_MAX,
//             если меньше INT32_MIN -> INT32_MIN, иначе честная сумма.
//    int32_t  sat_mul(int32_t a, int32_t b) — то же для умножения.
//    uint32_t wrap_add(uint32_t a, uint32_t b) — честное сложение по модулю 2^32.
//
//  ГЛАВНАЯ ЛОВУШКА: `a + b` для знакового типа при переполнении — это
//  НЕОПРЕДЕЛЁННОЕ ПОВЕДЕНИЕ. Нельзя сначала сложить, а потом проверить.
//  У меня проверка идёт с -fsanitize=undefined: наивное решение УПАДЁТ
//  с сообщением "runtime error: signed integer overflow", даже если
//  тесты формально пройдут. Обойти переполнение можно так:
//    - считать в int64_t и сравнивать с границами, ИЛИ
//    - проверять знаки операндов до сложения.
//
//  ВОПРОСЫ ДЛЯ ОТЧЁТА (в solutions/notes/M2.md):
//   1) Почему переполнение unsigned — это НЕ UB, а переполнение signed — UB?
//      Как ведёт себя `unsigned u = 0; u - 1`?
//   2) На платформе, где int32_t = int, что на самом деле происходит при
//      INT32_MAX + 1 в оптимизированном коде (-O2)? Почему компилятор имеет
//      право «сделать странно»?
//   3) Что такое two's complement и почему в нём на одно отрицательное число
//      больше, чем положительных?
// ============================================================
#include <cstdint>
#include <cstdio>

int32_t sat_add(int32_t a, int32_t b) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)a; (void)b;
    return 0;
    // >>> SOLUTION END
}

int32_t sat_mul(int32_t a, int32_t b) {
    // >>> SOLUTION2 START (меняй только здесь)
    // TODO: твой код
    (void)a; (void)b;
    return 0;
    // >>> SOLUTION2 END
}

uint32_t wrap_add(uint32_t a, uint32_t b) {
    // >>> SOLUTION3 START (меняй только здесь)
    // TODO: твой код
    (void)a; (void)b;
    return 0;
    // >>> SOLUTION3 END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void chk32(int32_t got, int32_t want, const char *what) {
    if (got != want) {
        if (want == INT32_MAX)      std::printf("FAIL %-26s got %d, want INT32_MAX\n", what, got);
        else if (want == INT32_MIN) std::printf("FAIL %-26s got %d, want INT32_MIN\n", what, got);
        else                        std::printf("FAIL %-26s got %d, want %d\n", what, got, want);
        ++g_fail;
    }
}
static void chku32(uint32_t got, uint32_t want, const char *what) {
    if (got != want) { std::printf("FAIL %-26s got %u, want %u\n", what, got, want); ++g_fail; }
}
int main() {
    chk32(sat_add(2, 3), 5, "2+3");
    chk32(sat_add(-2, -3), -5, "-2+-3");
    chk32(sat_add(INT32_MAX, 1), INT32_MAX, "MAX+1");
    chk32(sat_add(INT32_MAX, INT32_MAX), INT32_MAX, "MAX+MAX");
    chk32(sat_add(INT32_MIN, -1), INT32_MIN, "MIN-1");
    chk32(sat_add(INT32_MIN, INT32_MIN), INT32_MIN, "MIN+MIN");
    chk32(sat_add(INT32_MAX, INT32_MIN), -1, "MAX+MIN");
    chk32(sat_add(INT32_MAX - 10, 10), INT32_MAX, "MAX-10+10 (ровно впритык)");
    chk32(sat_add(INT32_MAX - 10, 11), INT32_MAX, "MAX-10+11 (чуть через край)");
    chk32(sat_add(0, 0), 0, "0+0");
    chk32(sat_add(-1, 1), 0, "-1+1");

    chk32(sat_mul(6, 7), 42, "6*7");
    chk32(sat_mul(-6, 7), -42, "-6*7");
    chk32(sat_mul(-6, -7), 42, "-6*-7");
    chk32(sat_mul(INT32_MAX, 2), INT32_MAX, "MAX*2");
    chk32(sat_mul(INT32_MIN, 2), INT32_MIN, "MIN*2");
    chk32(sat_mul(INT32_MIN, -1), INT32_MAX, "MIN*-1");
    chk32(sat_mul(0, INT32_MIN), 0, "0*MIN");
    chk32(sat_mul(1, INT32_MIN), INT32_MIN, "1*MIN");
    chk32(sat_mul(46341, 46341), INT32_MAX, "46341^2");   /* 2147488281 > INT32_MAX */
    chk32(sat_mul(46340, 46340), 2147395600, "46340^2");

    chku32(wrap_add(0xFFFFFFFFu, 1u), 0u, "UINT32_MAX+1");
    chku32(wrap_add(0xFFFFFFFFu, 0xFFFFFFFFu), 0xFFFFFFFEu, "MAX+MAX");
    chku32(wrap_add(2u, 3u), 5u, "2+3");

    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
