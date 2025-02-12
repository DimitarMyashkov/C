// zad 1
#include <stdio.h>

#define DEBUG

void sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sort_and_sum(int *arr, int size) {
    sort(arr, size);

#ifdef DEBUG
    printf("sorted arr: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
#endif

    int sum = 0;

    printf("elements at index divisible by 3: ");
    for (int i = 0; i < size; i++) {
        if (i % 3 == 0) {
            sum += arr[i];

#ifdef DEBUG
            printf("%d ", arr[i]);
#endif
        }
    }
    printf("\n");

    printf("sum: %d\n", sum);
}

int main() {
    int arr[] = {5, 8, 1, 3, 9, 6, 2, 7, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    sort_and_sum(arr, size);

    return 0;
}
