/* ============================================================
   L2-T2 · Структуры и сортировка
   Куда сдать: solutions/L2/L2-T2.c
   ============================================================ */
/*  Компиляция:  gcc -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined L2-T2.c -o t && ./t */
/*  Ожидание:    ALL TESTS PASSED */
/*  МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END. */
/*  ЗАДАЧА:
      void   sort_by_score(Student *s, size_t n);   по УБЫВАНИЮ score
      double average_score(const Student *s, size_t n);   для n==0 -> 0.0
    Сортировка любая (можно пузырьком), но БЕЗ выделения памяти и без qsort.
    ВАЖНО: менять местами нужно структуры ЦЕЛИКОМ (вместе с именем), а не только score.
    ВОПРОСЫ ДЛЯ ОТЧЁТА:
      1) Чем `Student *s` в параметрах отличается от `Student s[]`?
      2) Что скопируется при `Student b = a;` и сколько это байт?
      3) Почему у average_score параметр объявлен как `const Student *`?        */
#include <math.h>
#include <stddef.h>
#include <stdio.h>

typedef struct { char name[32]; int score; } Student;

void sort_by_score(Student *s, size_t n) {
    /* >>> SOLUTION START (меняй только здесь) */
    /* TODO: твой код */
    (void)s; (void)n;
    /* >>> SOLUTION END */
}

double average_score(const Student *s, size_t n) {
    /* >>> SOLUTION2 START (меняй только здесь) */
    /* TODO: твой код */
    (void)s; (void)n;
    return 0.0;
    /* >>> SOLUTION2 END */
}

/* -------------------- тесты: НЕ редактируй -------------------- */
static int g_fail = 0;
int main(void) {
    Student a[] = {
        {"Ivanov",  70}, {"Petrov", 95}, {"Sidorov", 80},
        {"Kotov",   60}, {"Myshov", 85}
    };
    const size_t n = sizeof a / sizeof a[0];
    sort_by_score(a, n);

    const int want_score[] = {95, 85, 80, 70, 60};
    const char want_first[] = {'P', 'M', 'S', 'I', 'K'};
    for (size_t i = 0; i < n; ++i) {
        if (a[i].score != want_score[i]) {
            printf("FAIL sort_by_score: [%zu].score = %d, ожидалось %d\n",
                   i, a[i].score, want_score[i]);
            ++g_fail;
        }
        if (a[i].name[0] != want_first[i]) {
            printf("FAIL sort_by_score: [%zu].name = \"%s\" — имя не переехало вместе со score\n",
                   i, a[i].name);
            ++g_fail;
        }
    }

    const double avg = average_score(a, n);
    if (fabs(avg - 78.0) > 1e-9) { printf("FAIL average_score: %f, ожидалось 78.0\n", avg); ++g_fail; }
    if (average_score(NULL, 0) != 0.0) { printf("FAIL average_score для пустого массива\n"); ++g_fail; }

    Student one[1] = {{"Solo", 42}};
    sort_by_score(one, 1);
    sort_by_score(NULL, 0);
    if (one[0].score != 42) { printf("FAIL n=1\n"); ++g_fail; }

    if (g_fail == 0) puts("ALL TESTS PASSED");
    else printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
