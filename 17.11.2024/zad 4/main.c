// zad 4
#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE 5

void raise_to_fourth_power(long arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (long)pow(arr[i], 4);
    }
}

void print_array(long arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");
}

int main() {
    long numbers[ARRAY_SIZE] = {1, 2, 3, 4, 5};

    printf("array: ");
    print_array(numbers, ARRAY_SIZE);

    raise_to_fourth_power(numbers, ARRAY_SIZE);

    printf("array at forth power: ");
    print_array(numbers, ARRAY_SIZE);

    return 0;
}
