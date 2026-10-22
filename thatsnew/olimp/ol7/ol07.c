#include <stdio.h>
#include <stdlib.h>

int array_max (int *array, size_t asize) {
    int most = array [0];
    for (size_t i = 0; i < asize; ++i) {
        if (array[i] == 10000) return array[i]; // По условию максимальный элемент массива - 10^4
        if (array[i] > most) most = array [i];
    }
    return most;
}

int main (void) {
    srand(0);
    size_t const N = (size_t)rand() % 100000 + 1; // По условию задачи размер массива не более 10^5
    printf ("Quantity of elements in array: [%zu]\n", N);
    int array[N];
    int d = 0;
    for (size_t i = 0; i < N; ++i) {
        array[i] = rand() % 20001 - 10000;
        if (i == 2) d = 1;
        if (N == 1) {
            printf ("[%d]\n", array[i]);
        }
        else if (N < 11) {
            printf ((i == 0) ? "[%d " : ((i == N - 1) ? "%d]\n" : "%d "), array[i]);
        }
        else if (i < 2 || i > N - 3) {
            printf ((i == 0) ? "[%d " : ((i == N-1) ? "%d]\n" : "%d "), array[i]);
        }
        else if (d == 1) {
            d = 0;
            printf ("... ");
        }
    }
    printf ("The biggest number in array is: %d\n", array_max (array, N));
    return 0;
}