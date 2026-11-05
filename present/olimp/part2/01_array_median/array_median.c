//Дан массив из N чисел. Найдите его медиану — значение, которое окажется в середине массива после сортировки.
//Если N чётное, выведите среднее арифметическое двух центральных элементов.
//1 <= N <= 100000

#include <stdio.h>

#define MAX_N 100000

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int median3 (int a, int b, int c) {
    if (a < b) {
        if (b < c) return b;
        return (a < c) ? c : a;
    } else {
        if (a < c) return a;
        return (b < c) ? c : b;
    }
}

static void quicksort (int *array, int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        int pivot = median3 (array[left], array[mid], array[right]);
        int mid_left = left;
        int i = left;
        int mid_right = right;
        while (i <= mid_right) {
            if (array[i] < pivot) {
                swap (&array[i], &array[mid_left]);
                ++i;
                ++mid_left;
            } else if (array[i] > pivot) {
                swap (&array[i], &array[mid_right]);
                --mid_right;
            } else {
                ++i;
            }
        }
        if (mid_left - left < right - mid_right) {
            quicksort (array, left, mid_left - 1);
            left = mid_right + 1;
        } else {
            quicksort (array, mid_right + 1, right);
            right = mid_left - 1;
        }
    }
}

int main (void) {
    int n = 0;
    static int array[MAX_N];
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf ("%d", &array[i]) != 1) {
            return 1;
        }
    }
    quicksort (array, 0, n - 1);
    if (n % 2 == 0) {
        printf ("%lld\n", ((long long)array[n / 2 - 1] + array[n / 2]) / 2);
    }
    else {
        printf ("%d\n", array[n / 2]);
    }
    return 0;
}