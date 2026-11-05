#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_N 100000
#define MAX_COORD 10000
#define MAX_LENGTH 20000

int main (void) {
    srand ((unsigned)time (NULL));
    FILE *file_w = fopen ("segments.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    int count = rand() % MAX_N + 1;
    fprintf (file_w, "%d\n", count);
    for (int i = 0; i < count; ++i) {
        int start = rand() % (2 * MAX_COORD + 1) - MAX_COORD;
        int length = rand() % MAX_LENGTH + 1;
        fprintf (file_w, "%d %d\n", start, start + length);
    }
    if (fclose (file_w) != 0) {
        printf ("Error occured. File wasn't closed.\n");
        return 1;
    }
    return 0;
}
