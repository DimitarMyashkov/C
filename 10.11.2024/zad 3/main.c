//zad 3
#include <stdio.h>

void bubble_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void selection_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}

void insertion_sort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void reverse_array(int *array, int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}

void sort(int *array, int size) {
    #if defined(_WIN32)
        printf("bubble sort for Windows\n");
        bubble_sort(array, size);
    #elif defined(__linux__)
        printf("selection sort for linux\n");
            selection_sort(array, size);
    #elif defined(__APPLE__)
            printf("insertion sortfor MacOS.\n");
            insertion_sort(array, size);
    #else
            printf("Обръщане на масива за непозната операционна система.\n");
            reverse_array(array, size);
    #endif
}

void print(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[6] = {3, 2, 9, 1, 5, 6};

    printf("before sort: ");
    print(array, 6);

    sort(array, 6);

    printf("after sort: ");
    print(array, 6);

    return 0;
}
