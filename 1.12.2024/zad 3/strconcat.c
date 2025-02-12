#include <stdio.h>
#include <string.h>
#include "mystrings.h"

#define SIZE 51

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    char str1[SIZE];
    char str2[SIZE];

    if (strlen(argv[1]) >= SIZE || strlen(argv[2]) >= SIZE) {
        printf("Error: Each string must be shorter than %d characters.\n", SIZE - 1);
        return 1;
    }

    strncpy(str1, argv[1], SIZE);
    strncpy(str2, argv[2], SIZE);

    strconcat(str1, str2);
    printf("%s\n", str1);
    return 0;
}
