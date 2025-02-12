// schoolroom.h
#ifndef SCHOOLROOM_H
#define SCHOOLROOM_H

#include "person.h"

typedef struct {
    int room_number;
    Person occupants[50];
} SchoolRoom;

#endif
