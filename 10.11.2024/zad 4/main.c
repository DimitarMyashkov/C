//zad 4
#include <stdio.h>
#include "schoolclass.h"
#include "schoolroom.h"

typedef struct {
    SchoolClass classes[20];
    SchoolRoom rooms[10];
} School;

int main() {
    School my_school;

    printf("school struct created successfully\n");

    return 0;
}
