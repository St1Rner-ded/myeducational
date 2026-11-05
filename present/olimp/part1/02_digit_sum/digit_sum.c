//Дано натуральное число N. Найдите сумму его цифр.
//1 <= N <= 10^18

#include <stdio.h>

#define MIN_N 1
#define MAX_N 1000000000000000000ull

int main (void) {
    size_t n = 0;
    size_t sum = 0;
    if (scanf("%zu", &n) != 1 || n < MIN_N || n > MAX_N) {
        return 1;
    }
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    printf ("%zu\n", sum);
    return 0;
}