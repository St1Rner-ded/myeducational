// ============================================================
//  L0-T3 · FizzBuzz в диапазоне
//  Куда сдать: solutions/L0/L0-T3.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L0-T3.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: fizzbuzz(from, to) печатает по одному значению В СТРОКУ
//  для каждого числа из [from; to]:
//     кратно 15 -> FizzBuzz,  кратно 3 -> Fizz,  кратно 5 -> Buzz,  иначе число.
//  Если from > to — не печатать ничего.
//  Ловушка: в C++ остаток от отрицательного числа отрицателен (-3 % 5 == -3),
//  поэтому проверка кратности должна работать и для отрицательных.
// ============================================================
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

void fizzbuzz(int from, int to) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)from; (void)to;
    // >>> SOLUTION END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static std::string capture(void (*f)(int, int), int a, int b) {
    std::ostringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());
    f(a, b);
    std::cout.rdbuf(old);
    return buf.str();
}
static void check(int a, int b, const std::string &want) {
    const std::string got = capture(fizzbuzz, a, b);
    if (got != want) {
        std::printf("FAIL fizzbuzz(%d, %d)\n  got : [%s]\n  want: [%s]\n",
                    a, b, got.c_str(), want.c_str());
        ++g_fail;
    }
}
int main() {
    check(1, 5,   "1\n2\nFizz\n4\nBuzz\n");
    check(9, 16,  "Fizz\nBuzz\n11\nFizz\n13\n14\nFizzBuzz\n16\n");
    check(15, 15, "FizzBuzz\n");
    check(5, 1,   "");
    check(-3, 0,  "Fizz\n-2\n-1\nFizzBuzz\n");
    check(-6, -5, "Fizz\nBuzz\n");
    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
