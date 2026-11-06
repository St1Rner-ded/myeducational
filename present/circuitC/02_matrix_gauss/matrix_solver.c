#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
    double *data;
    size_t cols;
    size_t rows;
} matrix;

void memory_init (matrix *mem) {
    mem->data = NULL;
    mem->cols = 0;
    mem->rows = 0;
}

void matrix_start (matrix *net) {
    memory_init (net);
    size_t n = 0;
    double x = 0.0;
    double v = 0.0;
    if (scanf ("%zu", &n) != 1) {
        free (net->data);
        exit (1);
    }
    net->cols = n + 1;
    net->rows = n;
    net->data = malloc (sizeof (*(net->data)) * net->rows * net->cols);
    if (net->data == NULL) {
        free (net->data);
        exit (1);
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (scanf ("%lf", &x) != 1) {
                free (net->data);
                exit (1);
            }
            net->data[i * net->cols + j] = x;
        }
    }
    for (size_t i = 0; i < n; i++) {
        if (scanf ("%lf", &v) != 1) {
            free (net->data);
            exit (1);
        }
        net->data[i * net->cols + n] = v;
    }
}

double abs_val (double a) {
    if (a >= 0) return a;
    return -a;
}

void swap (matrix *matr, size_t row_a, size_t row_b, size_t jig) {
    double tmp = matr->data[row_a * matr->cols + jig];
    matr->data[row_a * matr->cols + jig] = matr->data[row_b * matr->cols + jig];
    matr->data[row_b * matr->cols + jig] = tmp;
}



int main (void) {
    matrix jigsaw;
    matrix_start (&jigsaw);
    for (size_t k = 0; k < jigsaw.rows; k++) {
        size_t pivot = 0;
        double max = 0.0;
        for (size_t i = k; i < jigsaw.rows; i++) {
            if (abs_val (jigsaw.data[i * jigsaw.cols + k]) > max) {
                max = abs_val (jigsaw.data[i * jigsaw.cols + k]);
                pivot = i;
            }
        }
        if (max == 0.0) {
            free (jigsaw.data);
            return 1;
        }
        if (pivot != k) {
            for (size_t j = 0; j < jigsaw.cols; j++) {
                swap (&jigsaw, k, pivot, j);
            }
        }
        for (size_t i = k + 1; i < jigsaw.rows; i++) {
            double f = jigsaw.data[i * jigsaw.cols + k] / jigsaw.data[k * jigsaw.cols + k];
            for (size_t j = k; j < jigsaw.cols; j++) {
                jigsaw.data[i * jigsaw.cols + j] -= (f * jigsaw.data[k * jigsaw.cols + j]);
            }
        }
    }
    for (size_t i = 0; i < jigsaw.rows; i++) {
        for (size_t j = 0; j < jigsaw.cols; j++) {
            printf ("%f ", jigsaw.data[i * jigsaw.cols + j]);
        }
        printf ("\n");
    }
    for (size_t i = jigsaw.rows; i-- > 0;) {
        double sum_row = 0.0;
        for (size_t j = i + 1; j < jigsaw.rows; j++) {
            sum_row += (jigsaw.data[i * jigsaw.cols + j] * jigsaw.data[j * jigsaw.cols + jigsaw.rows]);
        }
        jigsaw.data[i * jigsaw.cols + jigsaw.rows] = (jigsaw.data[i * jigsaw.cols + jigsaw.rows] - sum_row) / jigsaw.data[i * jigsaw.cols + i];
    }
    printf ("\n");
    for (size_t i = 0; i < jigsaw.rows; i++) {
        printf ("%.6f ", jigsaw.data[i * jigsaw.cols + jigsaw.rows]);
    }
    printf ("\n");
    free (jigsaw.data);
    return 0;
}