#include <stdio.h>
#include <stdlib.h>

int main (void) {
    srand(0);
    size_t const N = (size_t)rand() % 100000 + 1;
    printf ("Quantity of elements in array: [%zu]\n", N);
    int array[N];
    for (size_t i = 0; i < N; ++i) {
        array[i] = rand() % 20001 - 10000;
    }
    int arr_sum = 0;
    for (size_t i = 0; i < N; ++i) {
        arr_sum += array[i];
    }
    printf ("Sum of all elements in array is: [%d]\n", arr_sum);
    return 0;
}