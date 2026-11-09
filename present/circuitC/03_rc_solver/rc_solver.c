//Uc(t) = E * (1 - e^(-t / RC))
//Ввод - E R C dt tmax

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_t {
    double *data;
    size_t rows;
    size_t cols;
} matrix_t;

typedef struct capacitor {
    double g_eq;
    double u;
    double i;
} capacitor;

typedef struct source {
    double u;
} source;

typedef struct resistor {
    double r;
    double g;
} resistor;

typedef struct simulation {
    double dt;
    double t_max;
} simulation;

static void data_init (matrix_t *A) {
    A->data = NULL;
    A->rows = 0;
    A->cols = 0;
}

static double abs_val (double a) {
    if (a >= 0) return a;
    return -a;
}

static void swap (matrix_t *m, size_t row_a, size_t row_b, size_t j) {
    double tmp = m->data[row_a * m->cols + j];
    m->data[row_a * m->cols + j] = m->data[row_b * m->cols + j];
    m->data[row_b * m->cols + j] = tmp;
}

static int matrix_solver (matrix_t *m) {
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

static void build_matrix (matrix_t *m, source *volt, capacitor *cap, resistor *cond) {
    m->data[0] = 1;
    m->data[1] = 0;
    m->data[2] = volt->u;
    m->data[3] = -(cond->g);
    m->data[4] = cond->g + cap->g_eq;
    m->data[5] = cap->g_eq * cap->u + cap->i;
}

int main (void) {
    matrix_t matr;
    double x[5] = {0.0};
    for (size_t i = 0; i < 5; i++) {
        if (scanf ("%lf", &x[i]) != 1) {
            return 1;
        }
    }
    source voltage;
    resistor conduct;
    capacitor cap;
    simulation sim;
    sim.dt = x[3];
    sim.t_max = x[4];
    voltage.u = x[0];
    conduct.r = x[1];
    conduct.g = 1.0 / conduct.r;
    cap.g_eq = 2 * x[2] / sim.dt;
    cap.u = 0.0;
    cap.i = voltage.u / conduct.r;
    data_init (&matr);
    matr.rows = 2;
    matr.cols = 3;
    matr.data = malloc (sizeof (*(matr.data)) * matr.rows * matr.cols);
    for (double t = sim.dt; t <= sim.t_max + sim.dt / 2; t += sim.dt) {
        build_matrix (&matr, &voltage, &cap, &conduct);
        matrix_solver (&matr);
        double Uc = matr.data[5];
        printf ("%f %f\n", t, Uc);
        double new_i = cap.g_eq * (Uc - cap.u) - cap.i;
        cap.u = Uc;
        cap.i = new_i;
    }
    free (matr.data);
    return 0;
}