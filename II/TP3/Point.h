#ifndef _POINT_H
#define _POINT_H

typedef struct {
    float x, y, z;
    char *name; //name of the point (can be null)
} Point;

Point createPointFromInputLine(char *str);
Point createPointFromStr(char *str);
Point createPoint(float x, float y, float z);

void resetPoint(Point *point);
void printPoint(Point point, char *label);

#endif

