#include <stdio.h>

int main (void) {
    char a = 'a';
    char A = 'A';
    char Z = 'Z';
    void *p = &a;
    void *q = &A;
    void *k = &Z;
    printf ("%d - %c - %p\n\n^\n|\n\n%d - %c - %p\n\n|\n|\n\n%d - %c - %p\n", A, A, q, a, a, p, Z, Z, k);
    return 0;
}