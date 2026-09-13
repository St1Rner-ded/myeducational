// ============================================================
//  L0-T2 · Простое число
//  Куда сдать: solutions/L0/L0-T2.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L0-T2.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: is_prime(n) = true, если n простое.
//    2 -> true,  1 -> false,  0 -> false,  -7 -> false,  97 -> true
//  ВОПРОС ДЛЯ ОТЧЁТА: до какого числа достаточно перебирать делители и почему?
//  Подсказка: 1000000007 должно проверяться мгновенно.
// ============================================================
#include <cstdio>

bool is_prime(long long n) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)n;
    return false;
    // >>> SOLUTION END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void check(bool got, bool want, long long n) {
    if (got != want) {
        std::printf("FAIL is_prime(%lld): got %s, want %s\n",
                    n, got ? "true" : "false", want ? "true" : "false");
        ++g_fail;
    }
}
int main() {
    const long long primes[] = {2, 3, 5, 7, 11, 13, 97, 7919, 999983, 1000000007LL};
    const long long not_pr[] = {-7, -1, 0, 1, 4, 9, 25, 100, 7920, 999984, 1000000006LL};
    for (long long p : primes) check(is_prime(p), true, p);
    for (long long p : not_pr) check(is_prime(p), false, p);
    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
