#include <stdio.h>
#include "mystrings.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string1> <string2>\n", argv[0]);
        printf("Description: Compares two strings lexicographically.\n");
        return 1;
    }

    int result = strcompare(argv[1], argv[2]);
    printf("Comparison result: %d\n", result);
    return 0;
}
