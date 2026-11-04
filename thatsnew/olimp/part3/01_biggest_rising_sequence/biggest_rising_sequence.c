//Дан массив из N чисел. Найдите длину наибольшей строго возрастающей подпоследовательности
//элементы не обязательно идут подряд, но сохраняют исходный порядок
//Первая строка — число N. Вторая строка — N целых чисел. - ВВОД
//Одно число — длина наибольшей возрастающей подпоследовательности. - ВЫВОД
//1 <= N <= 2500

#include <stdio.h>

#define MAX_N 2500

int main (void) {
    static int array[MAX_N + 1];
    int seq_len = 1;
    int n = 1;
    if (scanf ("%d", &n) != 1 || n == 0 || n > MAX_N) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        int z = 0;
        if (scanf ("%d", &z) != 1) {
            return 1;
        }
        array[i] = z;
    }
    static int len_array [MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        len_array[i] = 1;
    }
    for (int i = n - 1; i > -1; i--) {
        for (int j = i + 1; j < n; j++) {
            if (array[j] > array[i]) {
                if (len_array[i] < len_array[j] + 1) {
                    len_array[i] = len_array[j] + 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (len_array[i] > seq_len) seq_len = len_array[i];
    }
    printf ("%d\n", seq_len);
    return 0;
}