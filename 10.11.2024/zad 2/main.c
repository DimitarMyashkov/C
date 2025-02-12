// zad 2
#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
#if defined(ARRAY_SIZE) && ARRAY_SIZE > 0 && ARRAY_SIZE < 11
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1 << i;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("element %d: %d\n", i, array[i]);
    }
#else
    printf("error\n");
#endif

    return 0;
}
