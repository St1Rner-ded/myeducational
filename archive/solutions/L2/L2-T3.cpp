// ============================================================
//  L2-T3 · Динамический массив в куче
//  Куда сдать: solutions/L2/L2-T3.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L2-T3.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: create_range(from, to, out_len) возвращает указатель на массив,
//  ВЫДЕЛЕННЫЙ В КУЧЕ, заполненный from, from+1, ..., to.
//  Длину пишет в *out_len. Если from > to — вернуть nullptr и *out_len = 0.
//  Память освобождает вызывающий (тесты делают delete[] сами).
//  ВОПРОСЫ ДЛЯ ОТЧЁТА:
//    1) Что будет, если забыть delete[]? Чем это плохо в долгоживущей программе?
//    2) Почему вернуть локальный `int a[100]` из функции — ошибка?
//    3) Чем new[] отличается от malloc для типа int — а для типа Student?
// ============================================================
#include <cstddef>
#include <cstdio>

int *create_range(int from, int to, size_t *out_len) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)from; (void)to; (void)out_len;
    return nullptr;
    // >>> SOLUTION END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void check(int from, int to, const int *want, size_t want_len, const char *what) {
    size_t len = 12345;                       // заведомо мусор
    int *p = create_range(from, to, &len);
    if (want_len == 0) {
        if (p != nullptr) { std::printf("FAIL %s: ожидался nullptr\n", what); ++g_fail; }
        if (len != 0)     { std::printf("FAIL %s: out_len=%zu, ожидалось 0\n", what, len); ++g_fail; }
        delete[] p;
        return;
    }
    if (p == nullptr) { std::printf("FAIL %s: вернулся nullptr\n", what); ++g_fail; return; }
    if (len != want_len) {
        std::printf("FAIL %s: out_len=%zu, ожидалось %zu\n", what, len, want_len);
        ++g_fail;
    } else {
        for (size_t i = 0; i < len; ++i) {
            if (p[i] != want[i]) {
                std::printf("FAIL %s: [%zu]=%d, ожидалось %d\n", what, i, p[i], want[i]);
                ++g_fail;
                break;
            }
        }
    }
    delete[] p;
}
int main() {
    const int w1[] = {1, 2, 3, 4, 5};
    const int w2[] = {3};
    const int w3[] = {-2, -1, 0, 1, 2};
    const int w4[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    check(1, 5,  w1, 5,  "(1,5)");
    check(3, 3,  w2, 1,  "(3,3)");
    check(-2, 2, w3, 5,  "(-2,2)");
    check(5, 1,  nullptr, 0, "(5,1) пусто");
    check(0, 9,  w4, 10, "(0,9)");

    size_t len = 0;
    int *p = create_range(-1000, 1000, &len);
    if (p == nullptr || len != 2001 || p[0] != -1000 || p[2000] != 1000) {
        std::printf("FAIL (-1000,1000): len=%zu\n", len);
        ++g_fail;
    }
    delete[] p;

    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
