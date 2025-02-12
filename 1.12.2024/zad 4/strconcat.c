#include <stdio.h>
#include <string.h>
#include "mystrings.h"

#define MAX_SIZE 50

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string1> <string2>\n", argv[0]);
        printf("Description: Concatenates two strings into the first one.\n");
        printf("Note: Each string must be no longer than %d characters.\n", MAX_SIZE);
        return 1;
    }

    if (strlen(argv[1]) > MAX_SIZE || strlen(argv[2]) > MAX_SIZE) {
        printf("Error: Each string must be no longer than %d characters.\n", MAX_SIZE);
        return 1;
    }

    char str1[MAX_SIZE + 1]; // +1 за '\0'
    char str2[MAX_SIZE + 1];

    strncpy(str1, argv[1], MAX_SIZE + 1);
    strncpy(str2, argv[2], MAX_SIZE + 1);

    strconcat(str1, str2);
    printf("Concatenated string: %s\n", str1);
    return 0;
}
