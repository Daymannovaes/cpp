#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Point.h"
#include "Binder.h"

Binder createBinderFromStr(char *str) {
    return createBinder(str + (6 * sizeof(char)));
}

Binder createBinder(char *name) {
    Binder binder;

    binder.name = malloc(strlen(name) + 1 * sizeof(char));
    strcpy(binder.name, name);

    return binder;
}
