#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COUNT 1000ull

int main (void) {
    srand((unsigned)time(NULL));
    FILE *file_w = fopen ("rand_brackets_right.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    char ch;
    for (size_t i = 0; i < COUNT / 2; ++i) {
        int choice = rand() % 3 + 1;
        switch (choice) {
            case 1: {
                ch = '(';
                break;
            }
            case 2: {
                ch = '[';
                break;
            }
            case 3: {
                ch = '{';
                break;
            }
        }
        fprintf (file_w, "%c%c", ch, (ch == '(') ? ch + 1 : ch + 2);
    }
    return 0;
}