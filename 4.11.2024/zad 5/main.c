// zad 5
#include <stdio.h>

#define SWAP(A, B, TYPE) \
    do{\
        TYPE temp = A;   \
        A = B;           \
        B = temp;        \
    }while(0)


int main() {
    int x = 5, y = 10;
    float a = 3.14, b = 2.71;

    printf("before swap: %d %d\n", x, y);
    SWAP(x, y, int);
    printf("after swap: %d %d\n", x, y);

    printf("before swap: %f %f\n", a, b);
    SWAP(a, b, float);
    printf("after swap: %f %f\n", a, b);

    return 0;
}
