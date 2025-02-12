// zad 3
#include <stdio.h>

#define VALUE(x) x
#define NAME(x) #x
#define DEBUG_INSTRUMENT(x) \
    printf("The variable value is: %d\n", VALUE(x)); \
    printf("The variable name is: %s\n", NAME(x));   \
    printf("The line is: %d\n", __LINE__);           \
    printf("The file is: %s\n", __FILE__);

int main() {
    int var = 10;
    DEBUG_INSTRUMENT(var);

    return 0;
}