#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//f(Vd) = Is * (e ^ (Vd / (n * VT)) - 1) - (Vs - Vd) / R = 0
//f'(Vd) = Is / (n * VT) * e ^ (Vd / (n * VT)) + 1 / R
//Vd ^ (n + 1) = Vd ^ n - (f(vd) / f'(Vd))

typedef struct mtx_t {
    double *data;
    size_t rows;
    size_t cols;
} mtx_t;

typedef struct source {
    double u;
} source;

typedef struct resistor {
    double r;
    double g;
} resistor;

typedef struct diode {
    double Vd;
    double Is;
    double Id;
    double Ieq;
    double gd;
    double n;
    double VT;
    double Vcrit;
} diode;

static void data_init (mtx_t *A) {
    A->data = NULL;
    A->rows = 0;
    A->cols = 0;
}

static double abs_val (double a) {
    if (a >= 0) return a;
    return -a;
}

static void swap (mtx_t *m, size_t row_a, size_t row_b, size_t j) {
    double tmp = m->data[row_a * m->cols + j];
    m->data[row_a * m->cols + j] = m->data[row_b * m->cols + j];
    m->data[row_b * m->cols + j] = tmp;
}

static int matrix_solver (mtx_t *m) {
    for (size_t k = 0; k < m->rows; k++) {
        size_t pivot = 0;
        double max = 0.0;
        for (size_t i = k; i < m->rows; i++) {
            if (abs_val (m->data[i * m->cols + k]) > max) {
                max = abs_val (m->data[i * m->cols + k]);
                pivot = i;
            }
        }
        if (max == 0.0) {
            return (1);
        }
        if (pivot != k) {
            for (size_t j = 0; j < m->cols; j++) {
                swap (m, k, pivot, j);
            }
        }
        for (size_t i = k + 1; i < m->rows; i++) {
            double f = m->data[i * m->cols + k] / m->data[k * m->cols + k];
            for (size_t j = k; j < m->cols; j++) {
                m->data[i * m->cols + j] -= (f * m->data[k * m->cols + j]);
            }
        }
    }
    for (size_t i = m->rows; i-- > 0;) {
        double row_sum = 0.0;
        for (size_t j = i + 1; j < m->rows; j++) {
            row_sum += (m->data[i * m->cols + j] * m->data[j * m->cols + m->rows]);
        }
        m->data[i * m->cols + m->rows] = (m->data[i * m->cols + m->rows] - row_sum) / m->data[i * m->cols + i];
    }
    return 0;
}

static double dvolt_lim (diode *d, double v_old, double v_new) {
    if (v_new <= d->Vcrit) {
        return v_new;
    }
    if (v_new > v_old) {
        if (v_old <= 0.0) {
            return d->Vcrit;
        }
        return v_old + d->n * d->VT * log (1 + (v_new - v_old) / (d->n * d->VT));
    }
    return v_new;
}

static void build_matrix (mtx_t *m, source *volt, resistor *r, diode *d) {
    d->Id = d->Is * (exp (d->Vd / (d->n * d->VT)) - 1);
    d->gd = (d->Id + d->Is) / (d->n * d->VT);
    d->Ieq = d->Id - d->gd * d->Vd;
    m->data[0] = 1;
    m->data[1] = 0;
    m->data[2] = volt->u;
    m->data[3] = -r->g;
    m->data[4] = r->g + d->gd;
    m->data[5] = -d->Ieq;
}

int main (void) {
    mtx_t m;
    source voltage;
    resistor res;
    diode d;
    double x[4] = {0.0};
    for (size_t i = 0; i < 4; i++) {
        if (scanf ("%lf", &x[i]) != 1) {
            printf ("Ошибка ввода\n");
            return 1;
        }
    }
    voltage.u = x[0];
    res.r = x[1];
    res.g = 1 / res.r;
    d.Vd = 0.0;
    d.Is = x[2];
    d.n = x[3];
    d.VT = 0.026;
    d.Vcrit = d.n * d.VT * log (d.n * d.VT / (sqrt(2.0) * d.Is));
    data_init (&m);
    m.rows = 2;
    m.cols = m.rows + 1;
    m.data = malloc (sizeof (*(m.data)) * m.rows * m.cols);
    if (m.data == NULL) {
        printf ("Ошибка выделения памяти\n");
        free (m.data);
        return 1;
    }
    unsigned conv = 0;
    size_t max_iterations = 100;
    for (size_t i = 0; i < max_iterations; i++) {
        build_matrix (&m, &voltage, &res, &d);
        if (matrix_solver (&m) == 1) {
            free (m.data);
            return 1;
        }
        double dv_new = m.data[5];
        double dv_safe = dvolt_lim (&d, d.Vd, dv_new);
        if (fabs (dv_safe - d.Vd) < 0.000001) {
            d.Vd = dv_safe;
            conv = 1;
            break;
        }
        d.Vd = dv_safe;
    }
    if (!conv) {
        free (m.data);
        printf ("Несходимость за 100 итераций.\n");
        return 1;
    }
    printf ("%lf\n", d.Vd);
    free (m.data);
    return 0;
}