// 03-pointer-arithmetic.c — p + 1 сдвигает на sizeof(элемент) байт; q - p — число элементов.
// Тема: шаг указателя знает тип; разность двух указателей — это count, а не байты.
// Сборка/запуск — в README.md этой папки.

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int n_fail = 0;

static void check (int cond, const char *what) {
    if (!cond) {
        ++n_fail;
        printf ("FAIL: %s\n", what);
    }
}

int main (void) {
    int a[4] = {10, 20, 30, 40};
    int *p = a;
    int *q = a + 2;

    printf ("адрес p = %p\n", (void *) p);
    printf ("адрес q = %p\n", (void *) q);

    check ((size_t) (q - p) == 2, "q - p = 2 ЭЛЕМЕНТА: указатели считают объекты, а не байты");
    check (sizeof *p == 4, "один int = 4 байта");

    // Честное измерение шага в байтах: char* — единственный указатель,
    // у которого «один элемент = один байт».
    size_t step_bytes = (size_t) ((char *) (p + 1) - (char *) p);
    check (step_bytes == 4, "p + 1 сдвинул указатель ровно на sizeof(int) = 4 байта");

    // У char* «элемент» — это байт, но счёт всё равно идёт по элементам.
    char c[4] = {'a', 'b', 'c', 'd'};
    char *s = c;
    char *s3 = s + 3;
    check ((size_t) (s3 - s) == 3, "char*: и шаг, и разность — в байтах, потому что элемент = байт");
    check (*s3 == 'd', "s + 3 — это четвёртое место в c: индексы с нуля");

    // «Указатель за концом»: адрес вычислить МОЖНО, а вот *past_end — UB.
    int *past_end = a + 4;
    check ((char *) past_end == (char *) a + 4 * sizeof(int),
           "&a[4] легально: адрес конца существует, читать его содержимое нельзя");

    if (n_fail == 0) {
        printf ("OK: все проверки (03). Связка на память: шаг = sizeof(T), разность = кол-во T.\n");
    } else {
        printf ("ОТКАЗ: не прошли %d проверок (03)\n", n_fail);
    }
    return n_fail == 0 ? 0 : 1;
}
