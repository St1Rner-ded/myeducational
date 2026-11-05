//Дан массив из N чисел. Выведите его элементы в обратном порядке.
//1 <= N <= 100000

#include <stdio.h>

#define MAX_N 100000

int main (void) {
    int array[MAX_N + 1];
    int n = 0;
    if (scanf ("%d", &n) != 1 || n == 0 || n > MAX_N) {
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        int el = 0;
        if (scanf ("%d", &el) != 1) return 1;
        array[i] = el;
    }
    int rev_arr[MAX_N + 1];
    for (int i = 0; i < n; ++i) {
        rev_arr[i] = array[n - i - 1];
    }
    for (int i = 0; i < n; ++i) {
        printf ("%d ", rev_arr[i]);
    }
    return 0;
}