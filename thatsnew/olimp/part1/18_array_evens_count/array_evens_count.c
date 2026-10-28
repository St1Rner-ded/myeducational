//Дан массив из N чисел. Посчитайте, сколько среди них чётных.
//1 <= N <= 100000
//Вообще, в условии сказано, что надо ввести все числа в массив вручную, но я себе не представляю ручной ввод 10000 чисел
//Поэтому дал выбор: авто и ручное заполнение

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    srand((unsigned)time(NULL));
    int array[100000];
    size_t n = 0;
    char line[8];
    printf ("Enter array size: ");
    while (1) {
        if (fgets (line, sizeof (line), stdin) == NULL) {
            printf ("\nYou entered an emptiness. Exit.\n");
            return 1;
        }
        if (line[strlength (line) - 1] != '\n') {
            int c;
            while ((c = getchar ()) != '\n' && c != EOF) {
                ;
            }
        }
        if (sscanf (line, "%zu", &n) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (n == 0 || n > 100000) {
            printf ("Your number is 0 or too big. Try again: ");
            continue;
        }
        break;
    }
    printf ("Choose the variant of entering of elements:\n\n1 - auto\n2 - manual\nEnter: ");
    size_t choose = 0;
    while (1) {
        if (fgets (line, sizeof (line), stdin) == NULL) {
            printf ("\nYou entered an emptiness. Exit.\n");
            return 1;
        }
        if (line[strlength (line) - 1] != '\n') {
            int c;
            while ((c = getchar ()) != '\n' && c != EOF) {
                ;
            }
        }
        if (sscanf (line, "%zu", &choose) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (choose == 0 || choose > 2) {
            printf ("Your number is 0 or too big. Try again: ");
            continue;
        }
        break;
    }
    switch (choose) {
        case 1:
            for (size_t i = 0; i < n; ++i) {
                    array[i] = rand() % 100000 - 50000;
            }
            break;
        case 2: ;
            int num = 0;
            for (size_t i = 0; i < n; ++i) {
                while (1) {
                    if (fgets (line, sizeof (line), stdin) == NULL) {
                        printf ("\nYou entered an emptiness. Exit.\n");
                        return 1;
                    }
                    if (line[strlength (line) - 1] != '\n') {
                        int c;
                        while ((c = getchar ()) != '\n' && c != EOF) {
                            ;
                        }
                    }
                    if (sscanf (line, "%d", &num) != 1) {
                        printf ("You didn't enter a number. Try again: ");
                        continue;
                    }
                    if (num < -50000 || num > 50000) {
                        printf ("Your number is too low or too big. Try again: ");
                        continue;
                    }
                    break;
                }
                array[i] = num;
            }
    }
    printf ("\nYour array:\t");
    for (size_t i = 0; i < n; ++i) {
        printf ("%d ", array[i]);
    }
    unsigned even_count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (array[i] % 2 == 0) {
            ++even_count;
        }
    }
    printf ("\nYour array contains %u even numbers.\n", even_count);
    return 0;
}