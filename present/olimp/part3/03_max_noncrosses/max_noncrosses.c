//Дано N отрезков на числовой прямой, каждый задан началом и концом.
//Выберите наибольшее количество отрезков так, чтобы никакие два из них не пересекались.
//Отрезки могут соприкасаться концами — конец одного равен началу другого.
//ВВОД - Первая строка — число N. Следующие N строк — по два целых числа: начало и конец отрезка.
//ВЫВОД - Одно число — максимальное количество непересекающихся отрезков.
//1 <= N <= 100000

#include <stdio.h>

#define MAX_N 100000

typedef struct {
    int xs;
    int xe;
} segment;

static void seg_swap (segment *array, const int a, const int b) {
    int temp_s = array[a].xs;
    int temp_e = array[a].xe;
    array[a].xs = array[b].xs;
    array[a].xe = array[b].xe;
    array[b].xs = temp_s;
    array[b].xe = temp_e;
}

static int median (const int a, const int b, const int c) {
    if (a < b) {
        if (b < c) return b;
        return (a < c) ? c : a;
    }
    else {
        if (a < c) return a;
        return (b < c) ? c : b;
    }
}

static void quicksort (segment *array, int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        int pivot = median (array[left].xe, array[mid].xe, array[right].xe);
        int mid_left = left;
        int i = left;
        int mid_right = right;
        while (i <= mid_right) {
            if (array[i].xe < pivot) {
                seg_swap (array, i, mid_left);
                ++i;
                ++mid_left;
            }
            else if (array[i].xe > pivot) {
                seg_swap (array, i, mid_right);
                --mid_right;
            }
            else {
                ++i;
            }
        }
        if (mid_left - left < right - mid_right) {
            quicksort (array, left, mid_left - 1);
            left = mid_right + 1;
        }
        else {
            quicksort (array, mid_right + 1, right);
            right = mid_left - 1;
        }
    }
}

int main (void) {
    int n = 1;
    static segment array[MAX_N];
    unsigned quantity = 1;
    if (scanf ("%d", &n) != 1 || n == 0 || n > MAX_N) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            int z;
            if (scanf ("%d", &z) != 1) {
                return 1;
            }
            if (j == 0) array[i].xs = z;
            else array[i].xe = z;
        }
    }
    quicksort (array, 0, n - 1);
    int last_e = array[0].xe;
    for (int i = 1; i < n; i++) {
        if (array[i].xs >= last_e) {
            last_e = array[i].xe;
            quantity++;
        }
    }
    printf ("%u\n", quantity);
    return 0;
}