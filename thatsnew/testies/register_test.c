#include <stdio.h>

int main (void) {
    int a = 'a';
    int A = 'A';
    void *p = &a;
    void *q = &A;
    printf ("%d - %c - %p\n\n^\n|\n\n%d - %c - %p\n", A, A, q, a, a, p);
    return 0;
}