#ifndef _OCTREE_H
#define _OCTREE_H

typedef struct Octree {
    Point origin;
    Point halfDimension;

    int isLeaf;

    Point *data;

    struct Octree *children[8];

} Octree;

void insertPoint(Octree *octree, Point point);
void splitOctree(Octree *octree);
void createOctree(Octree **octree, Point origin, Point halfDimension);
int getChildIndex(Octree *octree, Point point);

Point calculateOrigin(Point pmax, Point pmin);
Point calculateHalfDimension(Point origin, Point pmax);

Point calculateMaxPoint(Point origin, Point edges);
Point calculateMinPoint(Point origin, Point edges);
Point calculateOctreeMaxPoint(Octree *octree);
Point calculateOctreeMinPoint(Octree *octree);

int getPointsInsideBox(Point binder, Octree *octree, double edge);

void freeOctree(Octree *octree);

#endif
