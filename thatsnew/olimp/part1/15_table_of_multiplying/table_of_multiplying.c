//Дано число N. Выведите таблицу умножения числа N на числа от 1 до 10.
//1 <= N <= 100

#include <stdio.h>

#define MAX_N 100

int main (void) {
    unsigned number = 0;
    if (scanf("%u", &number) != 1 || number == 0 || number > MAX_N) {
        return 1;
    }
    for (unsigned i = 1; i <= 10; ++i) {
        printf ("%u * %u\t= %u\n", number, i, number * i);
    }
    return 0;
}