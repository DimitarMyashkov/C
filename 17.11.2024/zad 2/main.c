// zad 2
#include <stdio.h>

int NOD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int NOK(int a, int b) {
    return (a * b) / NOD(a, b);
}

int main() {
    int a = 12, b = 18;
    printf("nok: %d\n", NOK(a, b));
    return 0;
}
