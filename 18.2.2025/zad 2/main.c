#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int main() {
    char str[MAX_LENGTH];

    if (fgets(str, sizeof(str), stdin)) {
        char *target = strchr(str, '\n');
        if (target) {
            *target = '\0';
        }
    }

    printf("%s", str);
    return 0;
}