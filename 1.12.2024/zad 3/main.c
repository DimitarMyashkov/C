//zad 3
#include <stdio.h>
#include "mystrings.h"

int main() {
   char str1[256] = "Hello";
    char str2[] = "World";

    printf("\nstrlength(\"%s\"): %zu\n", str1, strlength(str1));

    printf("\nstrconcat(\"%s\", \"%s\"):\n", str1, str2);
    strconcat(str1, str2);
    printf("result: %s\n", str1);

    printf("\nstrcompare(\"Alex\", \"Alan\"): %d\n", strcompare("Alex", "Alan"));
    printf("strcompare(\"Alex\", \"Alex\"): %d\n", strcompare("Alex", "Alex"));
    printf("strcompare(\"Alex\", \"Boyan\"): %d\n", strcompare("Alex", "Boyan"));

    return 0;
}
