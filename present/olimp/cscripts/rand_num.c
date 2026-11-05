#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COUNT 100000ull

int main (void) {
    srand((unsigned)time(NULL));
    FILE *file_w = fopen ("rand_numbers.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    fprintf (file_w, "%llu\n", COUNT);
    for (size_t i = 0; i < COUNT; ++i) {
        int number = rand();
        if (rand() % 2 == 0) number *= -1;
        fprintf (file_w, "%d ", number);
    }
    return 0;
}