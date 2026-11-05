#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COUNT 1000ull

int main (void) {
    srand((unsigned)time(NULL));
    FILE *file_w = fopen ("rand_brackets_wrong.txt", "w");
    if (file_w == NULL) {
        printf ("Error occured. File wasn't created.\n");
        return 1;
    }
    char ch;
    for (size_t i = 0; i < COUNT; ++i) {
        int choice = rand() % 6 + 1;
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
            case 4: {
                ch = ')';
                break;
            }
            case 5: {
                ch = ']';
                break;
            }
            case 6: {
                ch = '}';
                break;
            }
        }
        fprintf (file_w, "%c", ch);
    }
    return 0;
}