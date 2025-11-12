#include <stdio.h>

#define MAX 1000

struct Element {
    int value;
    int index;
};

void merge_value(struct Element arr[], int left, int mid, int right) {
    struct Element temp[MAX];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i].value >= arr[j].value) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

void merge_sort_value(struct Element arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_value(arr, left, mid);
        merge_sort_value(arr, mid + 1, right);
        merge_value(arr, left, mid, right);
    }
}

void merge_index(struct Element arr[], int left, int mid, int right) {
    struct Element temp[MAX];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i].index <= arr[j].index) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

void merge_sort_index(struct Element arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_index(arr, left, mid);
        merge_sort_index(arr, mid + 1, right);
        merge_index(arr, left, mid, right);
    }
}

int main() {
    int n, k;
    struct Element arr[MAX], chosen[MAX];

    printf("enter n: ");
    scanf("%d", &n);

    printf("enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].value);
        arr[i].index = i;
    }

    printf("enter k: ");
    scanf("%d", &k);

    merge_sort_value(arr, 0, n - 1);

    for (int i = 0; i < k; i++) {
        chosen[i] = arr[i];
    }

    merge_sort_index(chosen, 0, k - 1);

    printf("largest sum: ");
    int sum = 0;
    for (int i = 0; i < k; i++) {
        printf("%d ", chosen[i].value);
        sum += chosen[i].value;
    }
    printf("\nsum = %d\n", sum);

    return 0;
}
