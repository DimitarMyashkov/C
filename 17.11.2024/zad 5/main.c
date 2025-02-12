// zad 5
#include <stdio.h>
#include "maths.h"

int main() {
    int num = 5;
    long result = factorial(num);

    if (result != -1) {
        printf("Factorial of %d is %ld\n", num, result);
    } else {
        printf("Error: Factorial of a negative number is undefined.\n");
    }

    return 0;
}
