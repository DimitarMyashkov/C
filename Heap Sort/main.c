#include <stdio.h>

// O(n) + O(n log n) = O(n log n)

typedef unsigned int uint;

void swap (int *a, int *b) {
    int temp = 0;
    temp = *b;
    *b = *a;
    *a = temp;
}

void reorder(int *arr, uint count, uint parent) {
    uint largest = parent;
    uint l = 2 * parent + 1;
    uint r = 2 * parent + 2;

    if (l < count && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < count && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != parent) {
        swap(&arr[parent], &arr[largest]);
        reorder(arr, count, largest);
    }
}

void heapify (int *arr, uint count) {
    for (int i = count / 2 - 1; i >= 0; i--) {
        reorder(arr, count, i);
    }
}

void siftUp (int *arr, uint pos) {
    swap(&arr[0], &arr[pos]);

    uint parent = 0;
    uint left, right, largest;

    while (1) {
        left = 2 * parent + 1;
        right = 2 * parent + 2;

        if (left >= pos)
            break;

        largest = parent;

        if (left < pos && arr[left] > arr[largest])
            largest = left;

        if (right < pos && arr[right] > arr[largest])
            largest = right;

        if (largest == parent)
            break;

        swap(&arr[parent], &arr[largest]);
        parent = largest;
    }
}

void heapsort(int *arr, uint count) {
    heapify(arr, count);
    for (uint i = count - 1; i > 0; i--) {
        siftUp(arr, i);
    }
}

int main() {
    int arr[] = {2, 12, 8, 5, 28, 0};

    heapsort(arr, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}