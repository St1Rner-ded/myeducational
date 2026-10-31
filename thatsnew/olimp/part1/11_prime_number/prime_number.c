//Дано натуральное число N. Определите, является ли оно простым.
//1 ≤ N ≤ 10^6

#include <stdio.h>

#define MAX_N 1000000

int is_prime (const unsigned number) {
    if (number < 2) return 0;
    if (number % 2 == 0) {
        return (number == 2);
    }
    for (unsigned div = 3; div <= number / div; div += 2) {
        if (number % div == 0) return 0;
    }
    return 1;
}

int main (void) {
    unsigned number = 0;
    if (scanf ("%u", &number) != 1 || number == 0 || number > MAX_N) {
        return 1;
    }
    printf ((is_prime (number) == 1) ? "YES" : "NO");
    return 0;
}