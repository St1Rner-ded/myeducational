#include <stdio.h>
#include <stdlib.h>

typedef struct memory {
    int *data;
    size_t capacity;
    size_t size;
} memory;

void memory_init (memory *format) {
    format->capacity = 8;
    format->size = 0;
    format->data = malloc(sizeof(*(format->data)) * format->capacity);
    if (format->data == NULL) {
        free (format->data);
        exit (EXIT_FAILURE);
    }
}

void memory_expand (memory *format) {
    if (format->size != format->capacity) return;
    size_t new_cap = format->capacity * 2;
    int *tmp = realloc (format->data, sizeof (*(format->data)) * new_cap);
    if (tmp == NULL) {
        free (format->data);
        exit (EXIT_FAILURE);
    }
    format->data = tmp;
    format->capacity = new_cap;
}

int main (void) {
    memory our_data;
    memory_init (&our_data);
    int x = 0;
    int ic = 0;
    while ((ic = scanf ("%d", &x)) == 1) {
        our_data.data[our_data.size] = x;
        our_data.size += 1;
        memory_expand (&our_data);
    }
    if (ic == 0) {
        free(our_data.data);
        return 1;
    }
    long long sum = 0;
    for (size_t i = 0; i < our_data.size; i++) {
        sum += our_data.data[i];
    }
    printf ("%zu - size\n%zu - capacity\n%lld - sum", our_data.size, our_data.capacity, sum);
    free(our_data.data);
    return 0;
}