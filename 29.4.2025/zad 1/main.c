#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

void initArray(DynamicArray *arr, int capacity) {
    arr->data = (int *)malloc(capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = capacity;
}

void append(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int *)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = value;
}

int find_index(DynamicArray *arr, int value) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return i;
        }
    }
    return -1;
}

void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

int main() {
    DynamicArray arr;
    initArray(&arr, 4);

    append(&arr, 5);
    append(&arr, 10);
    append(&arr, 15);

    int index = find_index(&arr, 10);
    printf("index 10: %d\n", index);

    index = find_index(&arr, 99);
    printf("index 99: %d\n", index);

    freeArray(&arr);
    return 0;
}
