#include <stdio.h>

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

int main() {
    int x = 5, y = 10;

    printf("Watching first number: %d\n", compareasc(&x, &y));
    printf("Watching second number: %d\n", comparedesc(&x, &y));

    int a = 20, b = 20;
    printf("Equal values: %d\n", compareasc(&a, &b));

    return 0;
}
