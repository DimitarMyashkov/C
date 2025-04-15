#include <stdio.h>

typedef unsigned long long ull;
typedef ull (*func)(ull, ull);


ull add(ull a, ull b){
    return (a + b);
}

ull reduce(ull *arr, ull size, ull func(ull, ull), ull startValue){
    ull result = startValue;
    for (ull i = 0; i < size; i++) {
        result = func(result, arr[i]);
        printf("%llu \n", result);
    }
    return result;
}

int main() {
    ull arr[3] = {1, 2, 3};
    func ptr = add;

    ull result = reduce(arr, 3, ptr, 0);

    printf("the result is: %llu\n", result);

    return 0;
}