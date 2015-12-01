#ifndef _OCTREE_H
#define _OCTREE_H

typedef struct Octree {
    Point minPoint;
    Point maxPoint;

    int isLeaf;

    Point data;
    int hasData;

    struct Octree *children[8];

} Octree;

void insertPoint(Octree *octree, Point point);
void splitOctree(Octree *octree);
void insertPointInChild(Octree *octree, Point point);
Octree *findChild(Octree *octree, Point point);
int isPointInsideBox(Octree *octree, Point point);

float halfX(Octree *octree);
float halfY(Octree *octree);
float halfZ(Octree *octree);

void freeOctree(Octree *octree);

#endif
