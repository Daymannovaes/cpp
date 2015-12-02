#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

Point createPointFromInputLine(char *str) {
    char *delimiter = " ";

    strtok(str, delimiter);
    strtok(NULL, delimiter);

    return createPointFromStr(NULL);
}
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

void printPoint(Point point, char *label) {
    printf("\n\n\t (%s) Point", label);

    printf("\n\t (%f, %f, %f) \n\n", point.x, point.y, point.z);
}
