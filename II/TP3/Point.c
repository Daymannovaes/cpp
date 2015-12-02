#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

Point createPointFromStr(char *str) {
    char *delimiter = " ";
    float x, y, z;

    x = atof(strtok(str, delimiter));
    y = atof(strtok(NULL, delimiter));
    z = atof(strtok(NULL, "\n"));

    return createPoint(x, y, z);
}

Point createPoint(float x, float y, float z) {
    Point point;

    point.x = x;
    point.y = y;
    point.z = z;

    return point;
}

//used in getPointsInsideBox
void resetPoint(Point *point) {
    point->x = 0;
    point->y = 0;
    point->z = 0;
}
