#ifndef SCHOOLCLASS_H
#define SCHOOLCLASS_H

#include "person.h"

typedef struct {
    Person students[26];
    char section;
    int class_number;
    Person class_teacher;
} SchoolClass;

#endif
