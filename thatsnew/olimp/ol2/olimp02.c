#include <stdio.h>

int main (void) {
    unsigned long n = 0;
    unsigned long sum = 0;
    printf ("Enter your number: ");
    scanf ("%lu", &n);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    printf ("Sum of digits: %lu", sum);
    return 0;
}