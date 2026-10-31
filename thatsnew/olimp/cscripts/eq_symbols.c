#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
    srand((unsigned)time(NULL));
    FILE *file_w = fopen ("eq_symbols.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    int count = rand() % 1000 + 1;
    for (size_t i = 0; i < (size_t)count; ++i) {
        int number = rand() % 25 + 97;
        if (rand() % 5 == 0) number -= 32;
        fprintf (file_w, "%c", number);
    }
    return 0;
}