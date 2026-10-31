//Дано целое число от 0 до 20. Нужно вычислить факториал этого числа.

#include <stdio.h>

#define MIN_N 0
#define MAX_N 20

int main (void) {
    unsigned num = MIN_N;
    size_t factorial = 1;
    if (scanf("%u", &num) != 1 || num > MAX_N) {
        return 1;
    }
    for (unsigned i = 1; i <= num; ++i) {
        factorial *= i;
    }
    printf ("%zu\n", factorial);
    return 0;
}