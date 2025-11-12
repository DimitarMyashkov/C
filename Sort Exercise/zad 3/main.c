#include <stdio.h>

#define MAX 300

void sort_colors(int nums[], int n) {
    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            int temp = nums[low];
            nums[low] = nums[mid];
            nums[mid] = temp;
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            int temp = nums[mid];
            nums[mid] = nums[high];
            nums[high] = temp;
            high--;
        }
    }
}

int main() {
    int n;
    int nums[MAX];

    printf("num of elements: ");
    scanf("%d", &n);

    printf("elements (0, 1, or 2):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    sort_colors(nums, n);

    printf("sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
