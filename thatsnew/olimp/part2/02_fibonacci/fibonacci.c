#include <stdio.h>

#define MAX_N 80

int main (void) {
    unsigned n = 0;
    if (scanf ("%u", &n) != 1 || n == 0 || n > 80) {
        return 1;
    }
    size_t previous = 0, current = 0, next = 1;
    for (unsigned i = 0; i < n; ++i) {
        previous = current;
        current = next;
        next = previous + current;
    }
    printf ("%zu\n", current);
    return 0;
}