#include <stdio.h>

int strlen(const char *str) {
    const char *ptr = str;
    while (*ptr) {
        ptr++;
    }
    return ptr - str;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int *arr, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

void strhalf(char *str, char **half) {
    *half = str + strlen(str) / 2;
}

#define COL 4

void print(int (*matrix)[COL], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d\t", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

int main() {
    char str[] = "hello world";
    printf("length: %d\n", strlen(str));

    int arr[] = {5, 3, 8, 1, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    sort(arr, size);
    printf("sorted: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char *halfstr;
    strhalf(str, &halfstr);
    printf("half string: %s\n", halfstr);

    int matrix[3][COL] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
    };
    printf("matrix:\n");
    print(matrix, 3);

    return 0;
}
