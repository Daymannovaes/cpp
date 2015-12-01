#ifndef _POINT_H
#define _POINT_H

typedef struct {
    float x, y, z;
    char *name; //name of the point (can be null)
} Point;

Point createPoint(float x, float y, float z);
Point createPointFromStr(char *str);
Point createPointWithName(float x, float y, float z, char *name);

#endif

