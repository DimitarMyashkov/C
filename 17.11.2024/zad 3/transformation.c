#include "transformation.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static bool is_valid(const char *input) {
    if (*input == '-' || *input == '+') input++;
    if (!*input) return false;

    while (*input) {
        if (!isdigit(*input)) return false;
        input++;
    }
    return true;
}

transformation transform_string_to_long(const char *input) {
    transformation result;
    if (is_valid(input)) {
        result.result = strtol(input, NULL, 10);
        result.error[0] = '\0';
    } else {
        result.result = 0;
        strcpy(result.error, "Invalid input string");
    }
    return result;
}
