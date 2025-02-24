#include <stdio.h>

void swap(void *a, void *b) {
    int temp = *(int *) a;
    *(int*)a = *(int*)b;
    *(int*)b = temp;
}

int main() {
    int x = 5, y = 10;

    printf("x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    return 0;
}
