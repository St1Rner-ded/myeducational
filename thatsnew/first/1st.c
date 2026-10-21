#include <stdio.h>
#include <stdlib.h>

typedef struct intVector {
    int *data;
    size_t size;
    size_t capacity;
} intVector;

void init (intVector *vec) {
    vec->size = 0;
    vec->capacity = 0;
    vec->data = NULL;
}

static void reserve (intVector *vec, size_t new_capacity) {
    if (new_capacity <= vec->capacity) return;
    int *new_data = realloc (vec->data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        fprintf (stderr, "Ошибка выделения памяти!\n");
        exit(1);
    }
    vec->data = new_data;
    vec->capacity = new_capacity;
}

void push_back (intVector *vec, int value) {
    if (vec->size == vec->capacity) {
        if (vec->capacity == 0) reserve (vec, 1);
        else reserve (vec, vec->capacity * 2);
    }
    vec->data[vec->size] = value;
    ++vec->size;
}

void print (intVector *vec) {
    for (size_t i = 0; i < vec->size; ++i) {
        printf ("%d\n", vec->data[i]);
    }
}

void free_vec (intVector *vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

int main(void) {
    intVector vector;
    init (&vector);
    for (int i = 0; i < 15; ++i) {
        push_back (&vector, i * 10);
    }
    print (&vector);
    free_vec(&vector);
    return 0;
}