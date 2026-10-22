#include <stdio.h>

int main (void) {
    int n = 0;
    printf ("Enter your number: ");
    scanf("%d", &n);
    const char *str;
    str = (n % 2 == 0 ? "EVEN" : "ODD");
    printf ("%s\n", str);
    return 0;
}