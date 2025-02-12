// zad 1
#include <stdio.h>

#define SQUARE_SUM(A, B) ((A + B) * (A + B))

int main() {
    int a = 3, b = 4;
    int result = SQUARE_SUM(a, b);

    printf("result: %d\n", result);
    return 0;
}
