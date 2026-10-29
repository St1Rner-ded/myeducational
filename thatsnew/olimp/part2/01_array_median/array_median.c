//Дан массив из N чисел. Найдите его медиану — значение, которое окажется в середине массива после сортировки.
//Если N чётное, выведите среднее арифметическое двух центральных элементов.
//1 <= N <= 100000
//Вообще, в условии сказано, что надо ввести все числа в массив вручную, но я себе не представляю ручной ввод 10000 чисел
//Поэтому дал выбор: авто и ручное заполнение

#include <stdio.h>

size_t strlength (const char *string) {
    size_t n = 0;
    while (string[n] != '\0') {
        n++;
    }
    return n;
}

int main (void) {
    unsigned n = 0;
    char line[32];
    unsigned array[100000];
    printf ("Enter size of your array: ");
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
        if (sscanf (line, "%u", &n) != 1) {
            printf ("You didn't enter a number. Try again: ");
            continue;
        }
        if (n == 0 || n > 100000) {
            printf ("Your index is 0 or too big. Try again: ");
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
            printf ("Your number is not 1 or 2. Try again: ");
            continue;
        }
        break;
    }
    switch (choose) {
        case 1:
            for (size_t i = 0; i < n; ++i) {
                    array[i] = rand() % 100000+1;
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
                    if (num == 0 || num > 100000) {
                        printf ("Your number is too low or too big. Try again: ");
                        continue;
                    }
                    break;
                }
                array[i] = num;
            }
    }
    size_t len = strlength (array);
    while (1) {
        unsigned temp, sorts = 0;
        for (size_t i = 0; i < len; ++i) {
            if (array[i] > array[i + 1]) {
                temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
                sorts++;
            }
        }
        if (sorts == 0) break;
    }
    if (len % 2 == 0) {
        printf ("Array median: %u", (array [len / 2] + array [len / 2 + 1]) / 2);
    }
    return 0;
}