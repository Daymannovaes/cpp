#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Point.h"
#include "Octree.h"

void insertPoint(Octree *octree, Point point){
    if(octree->isLeaf) {
        if(octree->data == NULL) {

            octree->data = malloc(sizeof(Point));
            (*octree->data) = point;

        } else {
            octree->isLeaf = 0;

            splitOctree(octree); //create the 8 children

            int selfIndex = getChildIndex(octree, *octree->data);
            int newIndex = getChildIndex(octree, point);

            insertPoint(octree->children[selfIndex], *octree->data);
            free(octree->data);

            insertPoint(octree->children[newIndex], point);

        }
    } else {
        int newIndex = getChildIndex(octree, point);
        insertPoint(octree->children[newIndex], point);
    }
}

void splitOctree(Octree *octree) {
    int i;
    Point origin, halfDimension;
    float offset = 0.5;

    for(i=0; i<8; i++) {
        origin = octree->origin;

        halfDimension.x = offset*octree->halfDimension.x;
        halfDimension.y = offset*octree->halfDimension.y;
        halfDimension.z = offset*octree->halfDimension.z;

        origin.x += octree->halfDimension.x * (i&4 ? offset : -offset);
        origin.y += octree->halfDimension.y * (i&2 ? offset : -offset);
        origin.z += octree->halfDimension.z * (i&1 ? offset : -offset);

        createOctree(&octree->children[i], origin, halfDimension);
    }
}

void createOctree(Octree **octree, Point origin, Point halfDimension){
    int i;
    (*octree) = malloc(sizeof(Octree));

    (*octree)->origin = origin;
    (*octree)->halfDimension = halfDimension;
    (*octree)->isLeaf = 1;
    (*octree)->data = NULL;

    for(i=0; i<8; i++) {
        (*octree)->children[i] = NULL;
    }

}

int getChildIndex(Octree *octree, Point point){
    int index = 0;

    if(point.x >= octree->origin.x) index |= 4;
    if(point.y >= octree->origin.y) index |= 2;
    if(point.z >= octree->origin.z) index |= 1;

    return index;
}

Point calculateOrigin(Point pmax, Point pmin){
    Point origin;

    origin.x = (pmax.x + pmin.x)/2;
    origin.y = (pmax.y + pmin.y)/2;
    origin.z = (pmax.z + pmin.z)/2;

    return origin;
}

Point calculateHalfDimension(Point origin, Point pmax){
    Point halfDimension;

    float edge = sqrt(pow((pmax.x-origin.x),2) + pow((pmax.y-origin.y),2) + pow((pmax.z-origin.z),2)) / sqrt(3);

    halfDimension.x = edge;
    halfDimension.y = edge;
    halfDimension.z = edge;

    return halfDimension;
}

void freeOctree(Octree *octree) {
    int i;
    for (i=0; i<8; i++) {
        if (octree->children[i] != NULL) {
            if (octree->children[i]->isLeaf && octree->children[i]->data != NULL) {
                free(octree->children[i]->data);
                octree->children[i]->data = NULL;
            }

            freeOctree(octree->children[i]);
        }
    }
    free(octree);
}

int getPointsInsideBox(Point binder, Octree *octree, double edge) {
    int i;
    Point minPoint, maxPoint;
    Point edgep;

    edgep.x = edge/2;
    edgep.y = edge/2;
    edgep.z = edge/2;

    minPoint = calculateMinPoint(binder, edgep);
    maxPoint = calculateMaxPoint(binder, edgep);

    if(octree->isLeaf) {
        if(octree->data != NULL) {
            if(octree->data->x > maxPoint.x || octree->data->y > maxPoint.y || octree->data->z > maxPoint.z)
                return 0;
            if(octree->data->x < minPoint.x || octree->data->y < minPoint.y || octree->data->z < minPoint.z)
                return 0;

            return 1;
        }
    } else {
        int binderStength = 0;
        Point childMinPoint, childMaxPoint;
        for (i=0; i<8; i++) {
            childMinPoint = calculateOctreeMinPoint(octree->children[i]);
            childMaxPoint = calculateOctreeMaxPoint(octree->children[i]);


            if (childMaxPoint.x < minPoint.x || childMaxPoint.y < minPoint.y || childMaxPoint.z < minPoint.z)
                continue;
            if (childMinPoint.x > maxPoint.x || childMinPoint.y > maxPoint.y || childMinPoint.z > maxPoint.z)
                continue;

            binderStength += getPointsInsideBox(binder, octree->children[i], edge);
        }

        return binderStength;
    }
}


Point calculateMaxPoint(Point origin, Point edges) {
    Point point;

    point.x = origin.x + edges.x;
    point.y = origin.y + edges.y;
    point.z = origin.z + edges.z;

    return point;
}

Point calculateMinPoint(Point origin, Point edges) {
    edges.x = -edges.x;
    edges.y = -edges.y;
    edges.z = -edges.z;

    return calculateMaxPoint(origin, edges);
}

Point calculateOctreeMaxPoint(Octree *octree) {
    return calculateMaxPoint(octree->origin, octree->halfDimension);
}
Point calculateOctreeMinPoint(Octree *octree) {
    return calculateMinPoint(octree->origin, octree->halfDimension);
}


