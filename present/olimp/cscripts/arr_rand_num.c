#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COUNT 100000

int main (void) {
    srand((unsigned)time(NULL));
    FILE *file_w = fopen ("arr_rand_numbers.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    int count = rand() % COUNT + 1;
    fprintf (file_w, "%d\n", count);
    for (int i = 0; i < count; ++i) {
        int number = rand() % 10001;
        if (rand() % 2 == 0) number *= -1;
        fprintf (file_w, "%d ", number);
    }
    return 0;
}