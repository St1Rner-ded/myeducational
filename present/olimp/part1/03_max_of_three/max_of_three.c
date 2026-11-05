//Даны три целых числа. Найдите наибольшее из них.
//-(10^9) <= значения <= 10^9

#include <stdio.h>

#define MIN_N -1000000000
#define MAX_N 1000000000

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int max(const int a, const int b, const int c) {
    return (a >= b && a >= c) ? a : (b >= c) ? b : c;
}

int main (void) {
    int array[3];
    for (size_t i = 0; i < 3; ++i) {
        int n = 0;
        if (scanf("%d", &n) != 1 || n < MIN_N || n > MAX_N) {
        return 1;
        }
        array[i] = n;
    }
    printf("Max value is: %d\n", max (array[0], array[1], array[2]));
    return 0;
}