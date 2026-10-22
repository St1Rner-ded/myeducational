#include <stdio.h>

int main (void) {
    unsigned n = 0;
    printf ("Enter index of one of numbers of Fibonacci: ");
    while (1) {
        scanf("%u", &n);
        if (0 < n && n <= 80) break;
        else printf ("Your index is too big or zero. Try again.\n");
    }
    size_t previous = 0, current = 0, next = 1;
    for (unsigned i = 0; i < n; ++i) {
        previous = current;
        current = next;
        next = previous + current; 
    }
    printf ("Your number is: %zu\n", current);
    return 0;
}