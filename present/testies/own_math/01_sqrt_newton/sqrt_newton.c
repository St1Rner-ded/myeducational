#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ipow (double y, unsigned k) {
    unsigned n = k;
    double cur = y;
    double result = 1.0;
    while (n > 0) {
            if (n & 1) {
                result *= cur;
            }
            cur *= cur;
            n >>= 1;
    }
    return result;
}

void own_root (double a, unsigned k) {
    if (k == 1 || a == 0) {
        printf ("%f\n", a);
        return;
    }
    if (a < 0 && !(k & 1)) {
        fprintf (stderr, "Чётный корень из отрицательного числа не определён.\n");
        exit (1);
    }
    double A = fabs (a);
    double y = (a > 0) ? 1 : -1;
    double eth = pow (A, 1.0 / k);
    for (size_t i = 0; i < 100; i++) {
        double new_y = ((k - 1) * y + A / ipow (y, k - 1)) / k;
        if (fabs (new_y - eth) < 1E-6) {
            printf ("%zu: %f %f\n", i + 1, (k & 1 && a < 0) ? -new_y : new_y, eth);
            break;
        }
        printf ("%zu: %f %f\n", i + 1, (k & 1 && a < 0) ? -new_y : new_y, eth);
        y = new_y;
    }
}

int main (void) {
    double a = 0.0;
    unsigned k = 0;
    if (scanf ("%lf %u", &a, &k) != 2 || k == 0) {
        fprintf (stderr, "Нулевое значение для второго аргумента бессмысленно, либо вы ввели мусор.\n");
        return 1;
    }
    own_root (a, k);
    return 0;
}