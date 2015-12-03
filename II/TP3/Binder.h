#ifndef _BINDER_H
#define _BINDER_H

typedef struct {
    char *name;

    int strength;
} Binder;

Binder createBinderFromStr(char *str);
Binder createBinder(char *name);
#endif

