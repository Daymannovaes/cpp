#ifndef _BINDER_H
#define _BINDER_H

#include "Point.h"

int MAX_BINDER_POINTS = 100;
typedef struct {
    char *name;
    int pointCounter;
    Point *point;
} Binder;


Binder *createBinder(char *name);

int strIsBinderName(char *str);

#endif

