#include <stdio.h>

#define MAX 30000

void merge(int arr[], int left, int mid, int right) {
    int temp[MAX];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
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

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n, m;
    int g[MAX], s[MAX];

    printf("num of children: ");
    scanf("%d", &n);
    printf("greed factors:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &g[i]);

    printf("num of cookies: ");
    scanf("%d", &m);
    printf("cookie sizes:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &s[i]);

    merge_sort(g, 0, n - 1);
    merge_sort(s, 0, m - 1);

    int i = 0, j = 0;
    int content = 0;

    while (i < n && j < m) {
        if (s[j] >= g[i]) {
            content++;
            i++;
            j++;
        } else {
            j++;
        }
    }

    printf("max num content children: %d\n", content);

    return 0;
}
