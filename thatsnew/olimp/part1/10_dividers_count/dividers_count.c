//Дано натуральное число N. Найдите количество его натуральных делителей (включая 1 и само N)
//1 <= N <= 10^6

#include <stdio.h>

#define MAX_N 1000000

int main (void) {
    unsigned number = 0;
    unsigned divs_count = 1;
    if (scanf("%u", &number) != 1 || number == 0 || number > MAX_N) {
        return 1;
    }
    for (unsigned i = number - 1; i > 0; --i) {
        if (number % i == 0) ++divs_count;
    }
    printf ("%u\n", divs_count);
    return 0;
}