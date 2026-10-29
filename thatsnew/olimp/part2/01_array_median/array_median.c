//Дан массив из N чисел. Найдите его медиану — значение, которое окажется в середине массива после сортировки.
//Если N чётное, выведите среднее арифметическое двух центральных элементов.
//1 <= N <= 100000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    srand((unsigned)time(NULL));
    unsigned n = 0;
    char line[10];
    int array[100001];
    while (1) {
        if (fgets (line, sizeof (line), stdin) == NULL) {
            return 1;
        }
        if (line[strlength (line) - 1] != '\n') {
            int c;
            while ((c = getchar ()) != '\n' && c != EOF) {
                ;
            }
        }
        if (sscanf (line, "%u", &n) != 1) {
            continue;
        }
        if (n == 0 || n > 100000) {
            continue;
        }
        break;
    }
    for (unsigned i = 0; i < n; ++i) {
        if (scanf ("%d", &array[i]) != 1) {
            return 1;
        }
    }
    while (1) {
        int temp, sorts = 0;
        for (size_t i = 0; i < n - 1; ++i) {
            if (array[i] > array[i + 1]) {
                temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
                sorts++;
            }
        }
        if (sorts == 0) break;
    }
    if (n % 2 == 0) {
        printf ("%d\n", (array[n / 2 - 1] + array[n / 2]) / 2);
    }
    else {
        printf ("%d\n", array[n / 2]);
    }
    return 0;
}