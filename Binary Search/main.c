#include <stdio.h>

int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}


int main(void) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = 5;
    int target;

    printf("Enter the element to search: ");
    scanf("%d", &target);

    int result = binarySearch(arr, size, target);
    if (result == 1) {
        printf("Element found in the array.\n");
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}
