#include <stdio.h>

int max(int a, int b, int c) {
    return (a >= b && a >= c) ? a : (b >= c) ? b : c;
}

int check (long long x) {
    return (-1000000000 <= x && x <= 1000000000) ? 1 : 0;
}

int main (void) {
    long long a, b, c;
    printf ("Enter three numbers:\n");
    printf ("[1/3]\t");
    scanf ("%lld", &a);
    if (check(a) == 0) return 1; 
    printf ("[2/3]\t");
    scanf ("%lld", &b);
    if (check(b) == 0) return 1;
    printf ("[3/3]\t");
    scanf ("%lld", &c);
    if (check(c) == 0) return 1;
    printf("Max value is: %d", max ((int)a, (int)b, (int)c));
    return 0;
}