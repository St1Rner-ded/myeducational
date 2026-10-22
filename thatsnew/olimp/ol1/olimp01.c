#include <stdio.h>

int main (void) {
    int n = 0;
    printf ("Enter your number: ");
    scanf("%d", &n);
    printf ("%s\n", (n % 2 == 0) ? "EVEN" : "ODD");
    return 0;
}