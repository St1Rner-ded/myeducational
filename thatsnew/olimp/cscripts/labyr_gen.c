#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_RC 500
#define WALL_PERCENT 45

int main (void) {
    static char maze[MAX_RC][MAX_RC];
    srand ((unsigned)time (NULL));
    FILE *file_w = fopen ("labyr.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    int rows = 0;
    int collumns = 0;
    do {
        rows = rand() % MAX_RC + 1;
        collumns = rand() % MAX_RC + 1;
    } while (rows == 1 && collumns == 1);
    int start_row = rand() % rows;
    int start_col = rand() % collumns;
    int exit_row = rand() % rows;
    int exit_col = rand() % collumns;
    while (exit_row == start_row && exit_col == start_col) {
        exit_row = rand() % rows;
        exit_col = rand() % collumns;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < collumns; ++j) {
            maze[i][j] = rand() % 100 < WALL_PERCENT ? '#' : '.';
        }
    }
    int row = start_row;
    int col = start_col;
    while (row != exit_row || col != exit_col) {
        int can_move_row = row != exit_row;
        int can_move_col = col != exit_col;
        if (can_move_row && (!can_move_col || rand() % 2 == 0)) {
            row += row < exit_row ? 1 : -1;
        }
        else {
            col += col < exit_col ? 1 : -1;
        }
        maze[row][col] = '.';
    }
    maze[start_row][start_col] = 'S';
    maze[exit_row][exit_col] = 'E';
    fprintf (file_w, "%d %d\n", rows, collumns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < collumns; ++j) {
            fputc (maze[i][j], file_w);
        }
        fputc ('\n', file_w);
    }
    if (fclose (file_w) != 0) {
        printf ("Error occured. File wasn't closed.\n");
        return 1;
    }
    return 0;
}
