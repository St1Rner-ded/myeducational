//Даны два натуральных числа. Найдите их наибольший общий делитель.
//1 ≤ значения ≤ 10^9

#include <stdio.h>

#define MAX_N 1000000000

int main (void) {
    unsigned numbers[2];
    for (size_t i = 0; i < 2; ++i) {
        unsigned n = 0;
        if (scanf ("%u", &n) != 1 || n == 0 || n > MAX_N) {
            return 1;
        }
        numbers[i] = n;
    }
    if (numbers[1] > numbers[0]) {
        unsigned temp_num = numbers[0];
        numbers[0] = numbers[1];
        numbers[1] = temp_num;
    }
    while (numbers[0] % numbers[1] != 0) {
        unsigned modulo = numbers[0] % numbers[1];
        numbers[0] = numbers[1];
        numbers[1] = modulo;
    }
    printf ("%u", numbers[1]);
    return 0;
}