#include <stdio.h>

int main(void) {
    double a, b;

    scanf("%lf", &a);
    scanf("%lf", &b);

    double * ptra = &a;
    double * ptrb = &b;

    printf("Paths: a - %p, b - %p\n", ptra, ptrb);
    printf("Values: a - %lf, b - %lf\n", *ptra, *ptrb);

    return 0;
}
