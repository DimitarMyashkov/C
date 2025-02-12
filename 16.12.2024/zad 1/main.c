//zad 1
#include <stdio.h>
#include "quadraticroots.h"

void print(QuadraticRootsResult result) {
    if (result.norealroots) {
        printf("No real roots.\n");
    } else {
        printf("x1 = %Lf, x2 = %Lf\n", result.x1, result.x2);
    }
}

int main() {
    int a1 = 1, b1 = -3, c1 = 2;
    printf("int:\n");
    print(findroots(a1, b1, c1));

    float a2 = 1.0f, b2 = -4.5f, c2 = 4.0f;
    printf("\nfloat:\n");
    print(findroots(a2, b2, c2));

    double a3 = 1.0, b3 = 2.0, c3 = 5.0;
    printf("\ndouble:\n");
    print(findroots(a3, b3, c3));

    return 0;
}
