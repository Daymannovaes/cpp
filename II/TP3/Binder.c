#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"
#include "Binder.h"

int strIsBinderName(char *str) {
    return strstr(str, "Nome: ") != NULL;
}

int strIsBinderPoint(char *str) {
    return strstr(str, "LIGANTE ") != NULL;
}

int MAX_BINDER_POINTS = 100;
Binder *createBinder(char *name) {
    Binder *binder = malloc(sizeof(Binder));

    binder->pointCounter = 0;
    binder->point = malloc(MAX_BINDER_POINTS * sizeof(Point));
    binder->name = malloc(strlen(name) + 1 * sizeof(char));
    strcpy(binder->name, name);

    return binder;
}

void addBinderPoint(Binder *binder, char *str) {
    char *delimiter = " ";

    strtok(str, delimiter);
    strtok(NULL, delimiter);

    Point *point = createPointFromStr(NULL);

    binder->point[binder->pointCounter] = *point;
    binder->pointCounter++;
}
