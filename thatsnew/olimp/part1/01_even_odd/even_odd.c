//Дано целое число N. Определите, чётное оно или нечётное.
//-1000000000 <= N <= 1000000000

#include <stdio.h>

#define MIN_N -1000000000
#define MAX_N 1000000000

int main (void) {
    int n = 0;
    if (scanf("%d", &n) != 1 || n < MIN_N || n > MAX_N) {
        return 1;
    }
    printf ("%s\n", (n % 2 == 0) ? "EVEN" : "ODD");
    return 0;
}