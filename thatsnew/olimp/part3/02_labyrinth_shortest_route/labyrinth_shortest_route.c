//Дан прямоугольный лабиринт из символов «.» (проход), «#» (стена), «S» (старт) и «E» (выход).
//Найдите минимальное число шагов, чтобы попасть из S в E,
//перемещаясь на соседнюю клетку вверх, вниз, влево или вправо.
//Первая строка — числа R и C (число строк и столбцов). Следующие R строк — сам лабиринт. - ВВОД
//Одно число — минимальное количество шагов. Гарантируется, что путь существует. - ВЫВОД
//1 <= R, C <= 500 (условие одинаково и для R, и для C), S=E=1

#include <stdio.h>

#define MAX_RC 500

typedef struct {
    int row;
    int col;
} coords;

void check_sides (const int cur_row, const int cur_col, coords *queue, int (*distance)[MAX_RC], int *tail, const int next_row, const int next_col) {
    int *c = &distance[cur_row][cur_col];
    int *n = &distance[next_row][next_col];
    if (*n == -1) {
        *n = *c + 1;
        queue[*tail].row = next_row;
        queue[*tail].col = next_col;
        *tail += 1;
    }
    return;
}

int searching (const coords *info, char (*labyr)[MAX_RC + 2], const int rows, const int collumns) {
    static coords queue[MAX_RC * MAX_RC];
    static int distance[MAX_RC][MAX_RC];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < collumns; j++) {
            distance[i][j] = -1;
            if (i == info[0].row && j == info[0].col) {
                distance[i][j] = 0;
            }
        }
    }
    int head = 0, tail = 0;
    queue[tail].col = info[0].col;
    queue[tail].row = info[0].row;
    tail++;
    while (head < tail) {
        int cur_col = queue[head].col;
        int cur_row = queue[head].row;
        head++;
        if (cur_col + 1 < collumns) {
            if (labyr[cur_row][cur_col + 1] != '#') {
                check_sides (cur_row, cur_col, queue, distance, &tail, cur_row, cur_col + 1);
                if (labyr[cur_row][cur_col + 1] == 'E') {
                    return distance[cur_row][cur_col + 1];
                }
            }
        }
        if (cur_col - 1 > -1) {
            if (labyr[cur_row][cur_col - 1] != '#') {
                check_sides (cur_row, cur_col, queue, distance, &tail, cur_row, cur_col - 1);
                if (labyr[cur_row][cur_col - 1] == 'E') {
                    return distance[cur_row][cur_col - 1];
                }
            }
        }
        if (cur_row + 1 < rows) {
            if (labyr[cur_row + 1][cur_col] != '#') {
                check_sides (cur_row, cur_col, queue, distance, &tail, cur_row + 1, cur_col);
                if (labyr[cur_row + 1][cur_col] == 'E') {
                    return distance[cur_row + 1][cur_col];
                }
            }
        }
        if (cur_row - 1 > -1) {
            if (labyr[cur_row - 1][cur_col] != '#') {
                check_sides (cur_row, cur_col, queue, distance, &tail, cur_row - 1, cur_col);
                if (labyr[cur_row - 1][cur_col] == 'E') {
                    return distance[cur_row - 1][cur_col];
                }
            }
        }
    }
    return -1;
}

int main (void) {
    static char labyr[MAX_RC + 2][MAX_RC + 2];
    static coords info[2];
    int rows = 1, collumns = 1, start = 0, exit = 0;
    for (int i = 0; i < 2; i++) {
        int rc = 0;
        if (scanf ("%d", &rc) != 1 || rc == 0 || rc > MAX_RC) {
            return 1;
        }
        if (i == 0) rows = rc;
        else collumns = rc;
    }
    getchar();
    for (int i = 0; i < rows; i++) {
        if (fgets (labyr[i], sizeof (labyr[i]), stdin) == NULL) {
            return 1;
        }
        labyr[i][collumns] = '\0';
        for (int j = 0; j < collumns; j++) {
            if ((start != 0 && labyr[i][j] == 'S') || (exit != 0 && labyr[i][j] == 'E')) {
                return 1;
            }
            if (start == 0 && labyr[i][j] == 'S') {
                start = 1;
                info[0].row = i;
                info[0].col = j;
            }
            if (exit == 0 && labyr[i][j] == 'E') {
                exit = 1;
                info[1].row = i;
                info[1].col = j;
            }
        }
    }
    printf ("%d\n", searching (info, labyr, rows, collumns));
    return 0;
}