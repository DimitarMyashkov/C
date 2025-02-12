//zad 1
#include <stdio.h>
#include <string.h>

void strlength(const char *str);
void strconcat(const char *str1, const char *str2);
void strcompare(const char *str1, const char *str2);

int main() {
    char str1[] = "Hello";
    char str2[] = "World";

    printf("strlength(\"%s\"):\n", str1);
    strlength(str1);

    printf("\nstrconcat(\"%s\", \"%s\"):\n", str1, str2);
    strconcat(str1, str2);

    printf("\nstrcompare(\"%s\", \"%s\"):\n", str1, str2);
    strcompare(str1, str2);

    return 0;
}

void strlength(const char *str) {
    printf("string length: %lu\n", strlen(str));
}

void strconcat(const char *str1, const char *str2) {
    char result[256];
    snprintf(result, sizeof(result), "%s%s", str1, str2);
    printf("combined string: %s\n", result);
}

void strcompare(const char *str1, const char *str2) {
    int cmp = strcmp(str1, str2);
    if (cmp == 0) {
        printf("the strings are the same\n");
    } else if (cmp < 0) {
        printf("second string is larger\n");
    } else {
        printf("first string is larger\n");
    }
}
