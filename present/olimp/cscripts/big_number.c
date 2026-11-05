#include <stdio.h>

int main (void) {
    FILE *file_w = fopen ("big_numbers.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    fprintf (file_w, "%zu\n%zu\n", (size_t)1000000000, (size_t)1000000000000000000);
    return 0;
}