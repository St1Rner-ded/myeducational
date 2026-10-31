//Дан массив из N целых чисел. Найдите сумму всех его элементов.
//1 <= N <= 100000, -10000 <= elem <= 10000
//Здесь в рамках симуляции массив генерируется случайно

#include <stdio.h>

#define MAX_N 100000
#define MAX_ELEM 10000
#define MIN_ELEM -10000

int main (void) {
    int n = 0;
    static int array[MAX_N];
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        int z = 0;
        if (scanf ("%d", &z) != 1 || z < MIN_ELEM || z > MAX_ELEM) {
            return 1;
        }
        array[i] = z;
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += array[i];
    }
    printf ("%d", sum);
    return 0;
}