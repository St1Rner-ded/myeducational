// ============================================================
//  L0-T1 · Сумма цифр
//  Куда сдать: solutions/L0/L0-T1.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L0-T1.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: sum_digits(n) = сумма цифр числа по модулю.
//    123 -> 6,  0 -> 0,  -456 -> 15,  9999999999 -> 90
//  Крайние случаи: ноль, отрицательные, LLONG_MIN.
//  Ловушка: для LLONG_MIN запись (-n) даёт переполнение — подумай,
//  как перейти к беззнаковому типу безопасно.
// ============================================================
#include <climits>
#include <cstdio>

long long sum_digits(long long n) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    bool a=0;
    unsigned long long sum = 0;
    if (n==LLONG_MIN) {
        n++;
        a=1;
    }
    if (n<0) n*=(-1);
    while (n>0) {
        sum+=(n%10);
        n/=10;
    }
    if (a==1) sum++;
    return sum;
    // >>> SOLUTION END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void check(long long got, long long want, const char *what) {
    if (got != want) {
        std::printf("FAIL %-16s got %lld, want %lld\n", what, got, want);
        ++g_fail;
    }
}
int main() {
    check(sum_digits(123),             6,  "123");
    check(sum_digits(0),               0,  "0");
    check(sum_digits(7),               7,  "7");
    check(sum_digits(10),              1,  "10");
    check(sum_digits(-456),            15, "-456");
    check(sum_digits(-1000000000LL),   1,  "-10^9");
    check(sum_digits(9999999999LL),    90, "9999999999");
    check(sum_digits(1000000000LL),    1,  "10^9");
    check(sum_digits(1234567890123LL), 51, "1234567890123");
    check(sum_digits(LLONG_MAX),       88, "LLONG_MAX");
    check(sum_digits(LLONG_MIN),       89, "LLONG_MIN");
    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
