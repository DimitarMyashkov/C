#include <stdio.h>

union Number {
    long odd;
    short even;
};

int main() {
    union Number numbers[10];

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            numbers[i].even = i;
        } else {
            numbers[i].odd = i;
        }
    }

    printf("Values at odd indices:\n");
    for (int i = 1; i < 10; i += 2) {
        printf("Index %d: odd = %ld\n", i, numbers[i].odd);
    }

    printf("Values at even indices:\n");
    for (int i = 0; i < 10; i += 2) {
        printf("Index %d: even = %d\n", i, numbers[i].even);
    }

    return 0;
}
