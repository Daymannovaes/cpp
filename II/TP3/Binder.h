#ifndef _BINDER_H
#define _BINDER_H

#include "Point.h"

typedef struct {
    char *name;
    int pointCounter;
    Point *point;
} Binder;


Binder *createBinder(char *name);
void addBinderPoint(Binder *binder, char *str);

int strIsBinderName(char *str);
int strIsBinderPoint(char *str);

#endif

