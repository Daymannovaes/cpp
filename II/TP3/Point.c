#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

Point *createPointFromStr(char *str) {
    char *delimiter = " ";
    float x, y, z;

    x = atof(strtok(str, delimiter));
    y = atof(strtok(NULL, delimiter));
    z = atof(strtok(NULL, "\n"));

    return createPoint(x, y, z);
}
Point *createPoint(float x, float y, float z) {
    Point *point = malloc(sizeof(Point));

    point->x = x;
    point->y = y;
    point->z = z;

    return point;
}
Point *createPointWithName(float x, float y, float z, char *name) {
    Point *point = createPoint(x, y, z);

    point->name = malloc(strlen(name) + 1 * sizeof(char));
    strcpy(point->name, name);

    return point;
}
