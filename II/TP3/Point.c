#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

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
