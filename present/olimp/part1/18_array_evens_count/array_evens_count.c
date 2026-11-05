//Дан массив из N чисел. Посчитайте, сколько среди них чётных.
//1 <= N <= 100000

#include <stdio.h>

#define MAX_N 100000

int main (void) {
    int array[MAX_N + 1];
    int n = 0;
    int even_count = 0;
    if (scanf ("%d", &n) != 1 || n == 0 || n > MAX_N) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        int el;
        if (scanf ("%d", &el) != 1) {
            return 1;
        }
        array[i] = el;
    }
    for (int i = 0; i < n; i++) {
        even_count += (array[i] % 2 == 0) ? 1 : 0;
    }
    printf ("%d", even_count);
    return 0;
}