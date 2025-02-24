#include <stdio.h>

void swap(void *a, void *b) {
    int temp = *(int *) a;
    *(int*)a = *(int*)b;
    *(int*)b = temp;
}

int compareasc(const void *a, const void *b) {
    const int *ptra = (const int*)a;
    const int *ptrb = (const int*)b;

    if (*ptra > *ptrb) return 1;
    if (*ptra < *ptrb) return -1;
    return 0;
}

int comparedesc(const void *a, const void *b) {
    const int *ptra = (const int*)a;
    const int *ptrb = (const int*)b;

    if (*ptra < *ptrb) return 1;
    if (*ptra > *ptrb) return -1;
    return 0;
}

void bubblesort(void *arr, int n, int (*compare)(const void *, const void *), void (*swapelements)(void *, void *)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            void *a = &arr[j];
            void *b = &arr[j + 1];
            if (compare(a, b) > 0) {
                swapelements(a, b);
            }
        }
    }
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubblesort(arr, n, compareasc, swap);

    printf("sorted array ascending: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubblesort(arr, n, comparedesc, swap);

    printf("sorted array descending: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
