#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COUNT 100000ull

int main (void) {
    srand((unsigned)time(NULL));
    FILE *file_w = fopen ("eq_numbers.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    fprintf (file_w, "%llu\n", COUNT);
    int number = rand();
    if (rand() % 2 == 0) number *= -1;
    for (size_t i = 0; i < COUNT; ++i) {
        fprintf (file_w, "%d ", number);
    }
    return 0;
}