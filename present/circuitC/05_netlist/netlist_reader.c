#include <stdio.h>
#include <stdlib.h>

typedef struct netlist_t {
    char type;
    size_t index;
    size_t node_a;
    size_t node_b;
    double parameter_a;
    double parameter_b;
} netlist_t;

typedef struct mtx_t {
    double *data;
    size_t rows;
    size_t cols;
} mtx_t;

typedef struct sim_t {
    double dt;
    double tmax;
} sim_t;

static int nl_exp (netlist_t **n, size_t *cap, size_t *s) {
    if (*s < *cap) return 0;
    size_t new_cap = (*cap == 0) ? 1 : *cap * 2;
    netlist_t *new_n = realloc (*n, sizeof (**n) * new_cap);
    if (new_n == NULL) {
        fprintf (stderr, "Ошибка расширения списка компонентов.\n");
        return 1;
    }
    *cap = new_cap;
    *n = new_n;
    return 0;
}

int main (void) {
    int is_error = 0;
    size_t capacity = 1;
    size_t size = 0;
    sim_t simconsts;
    simconsts.dt = 1.0;
    simconsts.tmax = 1.0;
    netlist_t *netlist = malloc (sizeof (*netlist) * capacity);
    if (netlist == NULL) {
        fprintf (stderr, "Ошибка выделения памяти.\n");
        free (netlist);
        is_error = 1;
        return is_error;
    }
    char buf[256];
    size_t line_no = 0;
    while (fgets (buf, sizeof (buf), stdin) != NULL) {
        line_no++;
        netlist_t comp;
        if (buf[0] == 'V' || buf[0] == 'R' || buf[0] == 'C' || buf[0] == 'D') {
            if (buf[0] == 'D') {
                if (sscanf (buf, "%c%zu %zu %zu %lf %lf", &comp.type, &comp.index, &comp.node_a, &comp.node_b, &comp.parameter_a, &comp.parameter_b) != 6) {
                    fprintf (stderr, "Строка %zu: не разобрал компонент %s\n", line_no, buf);
                    is_error = 1;
                    break;
                }
            }
            else {
                if (sscanf (buf, "%c%zu %zu %zu %lf", &comp.type, &comp.index, &comp.node_a, &comp.node_b, &comp.parameter_a) != 5) {
                    fprintf (stderr, "Строка %zu: не разобрал компонент %s\n", line_no, buf);
                    is_error = 1;
                    break;
                }
                comp.parameter_b = 0;
            }
        } else if (buf[0] >= 'A' && buf[0] <= 'Z') {
            fprintf (stderr, "Строка %zu: неизвестный тип элемента.\n", line_no);
            is_error = 1;
            break;
        }
        else {
            if (sscanf (buf, "%lf %lf", &simconsts.dt, &simconsts.tmax) != 2) {
                fprintf (stderr, "Строка %zu: не разобрал постоянные симуляции\n", line_no);
                is_error = 1;
                break;
            }
            continue;
        }
        is_error = nl_exp (&netlist, &capacity, &size);
        netlist[size++] = comp;
    }
    if (is_error) {
        free (netlist);
        return is_error;
    }
    for (size_t i = 0; i < size; i++) {
        printf ("%c%zu %zu %zu %g %g\n", netlist[i].type, netlist[i].index, netlist[i].node_a, netlist[i].node_b, netlist[i].parameter_a, netlist[i].parameter_b);
    }
    printf ("%g %g\n", simconsts.dt, simconsts.tmax);
    free (netlist);
    return is_error;
}