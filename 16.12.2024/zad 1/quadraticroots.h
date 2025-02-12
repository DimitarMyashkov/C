#ifndef QUADRATICROOTS_H
#define QUADRATICROOTS_H

typedef struct {
    long double x1;
    long double x2;
    int norealroots;
} QuadraticRootsResult;

QuadraticRootsResult findroots(long double a, long double b, long double c);

#endif
