#include <stdio.h>

#define MAX_LIMBS 5000
#define LIMB_BASE 1000000000
#define MAX_N 1000

typedef struct bignum {
    unsigned limbs[MAX_LIMBS];
    unsigned used;
} bignum;

void bignum_mul(bignum *limbo, unsigned mul) {
    unsigned carry = 0;
    for (unsigned i = 0; i < limbo->used; ++i) {
        unsigned long long cur = (unsigned long long)limbo->limbs[i] * mul + carry;
        limbo->limbs[i] = (unsigned)(cur % LIMB_BASE);
        carry = (unsigned)(cur / LIMB_BASE);
    }
    if (carry > 0) {
        limbo->limbs[(limbo->used)++] = carry;
    }
}

int main (void) {
    bignum factorial_base = {.limbs = {1}, .used = 1};
    unsigned n = 1;
    if (scanf ("%u", &n) != 1 || n == 0 || n > MAX_N) {
        return 1;
    }
    for (unsigned k = 2; k <= n; k++) {
        bignum_mul (&factorial_base, k);
    }
    for (unsigned i = factorial_base.used - 1; i < factorial_base.used; i--) {
        if (i == factorial_base.used - 1) {
            printf ("%u ", factorial_base.limbs[i]);
        }
        else printf ("%09u ", factorial_base.limbs[i]);
    }
    printf ("\n");
    return 0;
}