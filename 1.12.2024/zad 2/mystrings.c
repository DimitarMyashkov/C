#include "mystrings.h"
#include <string.h>

size_t strlength(const char *str) {
    size_t length = 0;
    while (*str++) {
        length++;
    }
    return length;
}

void strconcat(char *str1, const char *str2) {
    while (*str1) {
        str1++;
    }
    while (*str2) {
        *str1++ = *str2++;
    }
    *str1 = '\0';
}

int strcompare(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    if (*str1 < *str2) {
        return -1;
    } else if (*str1 > *str2) {
        return 1;
    } else {
        return 0;
    }
}
