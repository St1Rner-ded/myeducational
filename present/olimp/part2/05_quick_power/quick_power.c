//Даны числа a и n. Вычислите aⁿ по модулю 1 000 000 007.
//Простое возведение в степень циклом за O(n) может не уложиться в ограничение времени
//при больших n потребуется алгоритм быстрого возведения в степень.
//1 <= a <= 10^9
//0 <= n <= 10^18
//Ввод - два целых a и n через пробел
//Вывод - одно число a^n mod 1000000007

#include <stdio.h>

#define MAX_a 1000000000
#define MAX_n 1000000000000000000
#define MOD 1000000007

int main (void) {
    size_t a = 0, n = 0, cur = 0, result = 1, k = 0;
    for (int i = 0; i < 2; i++) {
        size_t z = 0;
        if (scanf ("%zu", &z) != 1 || (i == 0 && (z > MAX_a || z == 0)) || (i == 1 && z > MAX_n)) {
            return 1;
        }
        if (i == 0) {
            a = z;
            cur = a;
        }
        else n = z;
    }
    while (n > 0) {
        if (n & 1) {
            result *= cur;
            result %= MOD;
        }
        cur *= cur;
        cur %= MOD;
        n >>= 1;
        k++;
    }
    printf ("%zu\n", result);
    return 0;
}