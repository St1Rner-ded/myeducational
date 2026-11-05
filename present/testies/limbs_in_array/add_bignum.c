#include <stdio.h>

#define MAX_N 1000
#define LIMB_BASE 1000000000
#define MAX_LIMBS 5000

typedef struct bignum {
    unsigned limbs[MAX_LIMBS];
    unsigned used;
} bignum;

void bignum_add (bignum *a, bignum *b) {
    unsigned carry = 0;
    unsigned actual_used = (b->used > a->used) ? b->used : a->used;
    for (unsigned i = 0; i < actual_used; i++) {
        unsigned long long sum = (unsigned long long)a->limbs[i] + b->limbs[i] + carry;
        a->limbs[i] = (unsigned)(sum % LIMB_BASE);
        carry = (unsigned)(sum / LIMB_BASE);
    }
    if (a->used < actual_used) {
        a->used = actual_used;
    }
    if (carry > 0) {
        a->limbs[(a->used)++] = carry;
    }
}

int main (void) {
    bignum prev = {{0}, 1};
    bignum cur = {{1}, 1};
    unsigned n = 1;
    if (scanf ("%u", &n) != 1 || n == 0 || n > MAX_N) {
        return 1;
    }
    for (unsigned k = 1; k <= n; k++) {
        if (k % 2 == 0) {
            bignum_add (&prev, &cur);
        }
        else {
            bignum_add (&cur, &prev);
        }
    }
    unsigned used = (n % 2 != 0) ? cur.used : prev.used;
    for (unsigned i = used - 1; i < used; i--) {
        if (i == used - 1) {
            printf ("%u ", (n % 2 != 0) ? cur.limbs[i] : prev.limbs[i]);
        }
        else {
            printf ("%09u ", (n % 2 != 0) ? cur.limbs[i] : prev.limbs[i]);
        }
    }
    printf ("\n");
    return 0;
}