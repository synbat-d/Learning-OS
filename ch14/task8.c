#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* data;      // dynamically allocated array
    int size;       // number of elements currently in use
    int capacity;   // total capacity of the array
} Vector;

void init_vector(Vector* vec) {
    vec->size = 0;
    vec->capacity = 4;  // initial capacity
    vec->data = malloc(vec->capacity * sizeof(int));
}

void push_back(Vector* vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;  // double the capacity
        vec->data = realloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size++] = value;
}

void free_vector(Vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

void print_vector(Vector* vec) {
    printf("Vector: ");
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", vec->data[i]);
    }
    printf("\n");
}

int main() {
    Vector myVec;
    init_vector(&myVec);

    for (int i = 1; i <= 10; i++) {
        push_back(&myVec, i * 10);
    }

    print_vector(&myVec);

    free_vector(&myVec);
    return 0;
}