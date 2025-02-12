#include <stdio.h>
#include "mystrings.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        printf("Description: Calculates the length of the provided string.\n");
        return 1;
    }

    size_t length = strlength(argv[1]);
    printf("Length: %zu\n", length);
    return 0;
}
