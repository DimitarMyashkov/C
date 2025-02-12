// zad 3
#include <stdio.h>
#include "transformation.h"

int main() {
    const char *valid_input = "-123";
    const char *invalid_input = "12ab23";

    transformation valid_result = transform_string_to_long(valid_input);
    transformation invalid_result = transform_string_to_long(invalid_input);

    if (valid_result.error[0] == '\0') {
        printf("Input: \"%s\" => Result: %ld, Error: \"%s\"\n", valid_input, valid_result.result, valid_result.error);
    } else {
        printf("Input: \"%s\" => Error: \"%s\"\n", valid_input, valid_result.error);
    }

    if (invalid_result.error[0] == '\0') {
        printf("Input: \"%s\" => Result: %ld, Error: \"%s\"\n", invalid_input, invalid_result.result, invalid_result.error);
    } else {
        printf("Input: \"%s\" => Error: \"%s\"\n", invalid_input, invalid_result.error);
    }

    return 0;
}
