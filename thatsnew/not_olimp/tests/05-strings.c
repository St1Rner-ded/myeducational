// 05-strings.c — строка это char с \0; char[] против char* (SPRAVOCHNIK.md §3.3).
// Тема: разборка «что внутри char*', когда ты её читаешь/меняешь» и почему p[0]='H' — это UB.
// Сборка/запуск — в README.md этой папки.

#include <stdio.h>
#include <stdlib.h>

static int n_fail = 0;

static void check (int cond, const char *what) {
    if (!cond) {
        ++n_fail;
        printf ("FAIL: %s\n", what);
    }
}

// Минимальная длина строки «руками»: идём по char*, пока не найдём \0.
static size_t my_len (const char *s) {
    size_t n = 0;
    while (s[n] != '\0') ++n;
    return n;
}

// Палиндром через два указателя — тот же, что будет в olimp/ol8 (без std::).
static int is_palindrome (const char *s) {
    const char *l = s;
    const char *r = s + my_len (s) - 1;
    while (l < r) {
        if (*l != *r) return 0;
        ++l;
        --r;
    }
    return 1;
}

int main (void) {
    char buf[] = "hello";        // массив из 6 char в стеке: 'h', 'e', 'l', 'l', 'o', '\0'
    char *ptr = "world";         // 8-байтный указатель на литерал, который живёт в .rodata

    printf ("sizeof buf = %zu\n", sizeof buf);
    printf ("sizeof ptr = %zu\n", sizeof ptr);
    printf ("%p\n", (void *) &buf[0]);

    check (sizeof buf == 6, "char[6] в стеке: пять символов + \0; sizeof видит весь массив");
    check (sizeof ptr == 8, "char* — сам указатель: 8 байт, где бы строка ни была");
    check ((void *) &buf[0] == (void *) buf, "адрес массива = адрес его первого символа (значения равны)");

    // buf менять МОЖНО: данные лежат в стеке, \0 уже внутри.
    buf[0] = 'H';
    check (my_len (buf) == 5 && buf[0] == 'H', "buf[0] = 'H' легально: это данные, а не литерал; длина не изменилась");

    // ptr менять НЕЛЬЗЯ: литерал в read-only сегменте. *ptr = 'W' даёт SIGSEGV,
    // поэтому в этом тесте через ptr только ЧИТАЕМ.
    check (my_len (ptr) == 5, "my_len по char* ходит за счёт \0: длина здесь — 5");
    check (is_palindrome ("level") == 1 && is_palindrome ("abcd") == 0 && is_palindrome ("") == 1,
           "палиндром: «level» — да, «abcd» — нет, пустая строка — да (краевой случай)");

    // Почему my_len здесь работает без sizeof: он просто ищет \0.
    // Отсюда правило: функция, получающая char*, уходит за \0, если его нет.
    char frag[3] = {'a', 'b', 'c'};      // БЕЗ \0: my_len (frag) уйдёт в чужую память
    // Поэтому фрагменты без \0 передаём С ДОЛИНОЙ: (frag, sizeof frag).
    check (frag[1] == 'b', "фрагмент без \0 не строка: его смысл передаётся парой (указатель, длина)");

    if (n_fail == 0) {
        printf ("OK: все проверки (05). Строка в C = char* + обязательный нулевой символ в конце. Всё остальное — следствия.\n");
    } else {
        printf ("ОТКАЗ: не прошли %d проверок (05)\n", n_fail);
    }
    return n_fail == 0 ? 0 : 1;
}
