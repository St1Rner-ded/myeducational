// ============================================================
//  L1-T2 · Палиндром «по-человечески»
//  Куда сдать: solutions/L1/L1-T2.cpp
// ============================================================
//  Компиляция:  g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L1-T2.cpp -o t && ./t
//  Ожидание:    ALL TESTS PASSED
//  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END.
//  ЗАДАЧА: is_palindrome(s) = true, если строка — палиндром, игнорируя регистр
//  и все символы кроме букв латиницы.
//    "A man, a plan, a canal: Panama" -> true
//    "abc" -> false,   "" -> true,   "12321" -> true,   ".,!" -> true
//  Ограничение: НЕ создавать вторую строку/вектор. Два индекса — с начала и с конца.
// ============================================================
#include <cstdio>
#include <string>

bool is_palindrome(const std::string &s) {
    // >>> SOLUTION START (меняй только здесь)
    // TODO: твой код
    (void)s;
    return false;
    // >>> SOLUTION END
}

// -------------------- тесты: НЕ редактируй --------------------
static int g_fail = 0;
static void check(const std::string &s, bool want) {
    const bool got = is_palindrome(s);
    if (got != want) {
        std::printf("FAIL \"%s\": got %s, want %s\n", s.c_str(),
                    got ? "true" : "false", want ? "true" : "false");
        ++g_fail;
    }
}
int main() {
    check("", true);
    check("A", true);
    check("aa", true);
    check("ab", false);
    check("abc", false);
    check("racecar", true);
    check("RaceCar", true);
    check("A man, a plan, a canal: Panama", true);
    check("No 'x' in Nixon", true);
    check("12321", true);
    check(".,!", true);
    check("hello world", false);
    check("ab,cba", true);
    check("a b", false);        /* буквы "ab" — не палиндром */
    check("a b a", true);       /* буквы "aba" — палиндром */
    if (g_fail == 0) std::puts("ALL TESTS PASSED");
    else std::printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
