#ifndef MYSTRINGS_H
#define MYSTRINGS_H

#include <stddef.h>

size_t strlength(const char *str);

void strconcat(char *str1, const char *str2);

int strcompare(const char *str1, const char *str2);

#endif
