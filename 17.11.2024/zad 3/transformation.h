#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <stdbool.h>

typedef struct {
    long result;
    char error[100];
} transformation;

transformation transform_string_to_long(const char *input);

#endif // TRANSFORMATION_H
