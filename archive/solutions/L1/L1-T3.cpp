// ============================================================
//  L1-T3 · Второе по величине
//  Куда сдать: solutions/L1/L1-T3.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L1-T3.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: second_largest(a, n) = второе по значению среди РАЗЛИЧНЫХ элементов.
//  Один проход, без сортировки, O(1) памяти.
//  Если различных элементов меньше двух — вернуть INT_MIN.
//    {1,2,3} -> 2      {5,5,5} -> INT_MIN     {3,1} -> 1
//    {}      -> INT_MIN                       {-5,-1} -> -5
//  Ловушка: нельзя инициализировать «максимумы» значением INT_MIN и потом
//  просто сравнивать — если в массиве реально лежит INT_MIN, результат совпадёт
//  с «не найдено». Держи отдельные флаги found1 / found2.
// ============================================================
#include <climits>
#include <cstddef>
#include <cstdio>

int second_largest(const int *a, size_t n) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)a; (void)n;
    return 0;
    // >>> SOLUTION END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void check(const int *a, size_t n, int want, const char *what) {
    const int got = second_largest(a, n);
    if (got != want) {
        if (want == INT_MIN) std::printf("FAIL %-16s got %d, want INT_MIN\n", what, got);
        else                 std::printf("FAIL %-16s got %d, want %d\n", what, got, want);
        ++g_fail;
    }
}
int main() {
    const int t1[] = {1, 2, 3};      check(t1, 3, 2, "{1,2,3}");
    const int t2[] = {3, 2, 1};      check(t2, 3, 2, "{3,2,1}");
    const int t3[] = {5, 5, 5};      check(t3, 3, INT_MIN, "{5,5,5}");
    const int t4[] = {3, 1};         check(t4, 2, 1, "{3,1}");
    check(nullptr, 0, INT_MIN, "{}");
    const int t5[] = {42};           check(t5, 1, INT_MIN, "{42}");
    const int t6[] = {-5, -1};       check(t6, 2, -5, "{-5,-1}");
    const int t7[] = {-1, -2, -3};   check(t7, 3, -2, "{-1,-2,-3}");
    const int t8[] = {10, 10, 9};    check(t8, 3, 9, "{10,10,9}");
    const int t9[] = {1, 2};         check(t9, 2, 1, "{1,2}");
    const int t10[] = {2, 1};        check(t10, 2, 1, "{2,1}");
    const int t11[] = {INT_MIN, 0};  check(t11, 2, INT_MIN, "{INT_MIN,0}");
    const int t12[] = {5, 1, 5, 2};  check(t12, 4, 2, "{5,1,5,2}");
    int big[1000];
    for (int i = 0; i < 1000; ++i) big[i] = i;
    check(big, 1000, 998, "0..999");
    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
