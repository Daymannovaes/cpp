#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Point.h"
#include "Octree.h"

int i;
void insertPoint(Octree *octree, Point *point) {
    i++;
    printf("\n\t test");
    printf("\n\n\t (%d) Inserindo (%f, %f, %f)", i, point->x, point->y, point->z);
    printf("\n\t Dentro de (%f, %f, %f) e (%f, %f, %f)", octree->minPoint.x, octree->minPoint.y, octree->minPoint.z, octree->maxPoint.x, octree->maxPoint.y, octree->maxPoint.z);
    printf("\n\t isLeaf: %d", octree->isLeaf);
    printf("\n\t dataNull: %d", octree->data == NULL);
    printf("\n\t child[0]Null: %d\n", octree->children[0] == NULL);

    if(octree->isLeaf) {
        if(octree->data == NULL) {
                printf("\na\n");
            octree->data = (Point *)malloc(sizeof(Point));
                printf("\nb\n");
            octree->data = point;
                printf("\nc\n");
            return;
        }
        else {
            octree->isLeaf = 0;
            insertPoint(octree, octree->data);
            insertPoint(octree, point);
            return;
        }
    }
    else {
        Octree *child;

        if(octree->children[0] == NULL)
            splitOctree(octree); //create the 8 children

        child = findChild(octree, point);
        insertPoint(child, point);
        return;
    }
}

void freeOctree(Octree *octree) {
    int i;

    for(i=0; i<8; i++) {
        if(octree != NULL && octree->children != NULL && octree->children != &octree->children)
            freeOctree(octree->children[i]);
    }
    free(octree);
}

void splitOctree(Octree *octree) {
    int i;
    float _halfX = halfX(octree);
    float _halfY = halfY(octree);
    float _halfZ = halfZ(octree);

    for(i=0; i<8; i++) {
        octree->children[i] = (Octree *)malloc(sizeof(Octree));
        octree->children[i]->isLeaf = 1;
        octree->children[i]->data = NULL;
    }

    octree->children[0]->minPoint = *createPoint(octree->minPoint.x, octree->minPoint.y, octree->minPoint.z);
    octree->children[0]->maxPoint = *createPoint(_halfX, _halfY, _halfZ);

    octree->children[1]->minPoint = *createPoint(_halfX, octree->minPoint.y, octree->minPoint.z);
    octree->children[1]->maxPoint = *createPoint(octree->maxPoint.x, _halfY, _halfZ);

    octree->children[2]->minPoint = *createPoint(octree->minPoint.x, _halfY, octree->minPoint.z);
    octree->children[2]->maxPoint = *createPoint(_halfX, octree->maxPoint.y, _halfZ);

    octree->children[3]->minPoint = *createPoint(_halfX, _halfY, octree->minPoint.z);
    octree->children[3]->maxPoint = *createPoint(octree->maxPoint.x, octree->maxPoint.y, _halfZ);

    octree->children[4]->minPoint = *createPoint(octree->minPoint.x, octree->minPoint.y, _halfZ);
    octree->children[4]->maxPoint = *createPoint(_halfX, _halfY, octree->maxPoint.z);

    octree->children[5]->minPoint = *createPoint(_halfX, octree->minPoint.y, _halfZ);
    octree->children[5]->maxPoint = *createPoint(octree->maxPoint.x, _halfY, octree->maxPoint.z);

    octree->children[6]->minPoint = *createPoint(octree->minPoint.x, _halfY, _halfZ);
    octree->children[6]->maxPoint = *createPoint(_halfX, octree->maxPoint.y, octree->maxPoint.z);

    octree->children[7]->minPoint = *createPoint(_halfX, _halfY, _halfZ);
    octree->children[7]->maxPoint = *createPoint(octree->maxPoint.x, octree->maxPoint.y, octree->maxPoint.z);
}

Octree *findChild(Octree *octree, Point *point) {
    int i;

    for(i=0; i<8; i++) {
        if(isPointInsideBox(octree->children[i], point))
            return octree->children[i];
    }

    for(i=0; i<8; i++) {
        printf("\n\n\t Procurando em \n\t (%f, %f, %f) \n\t (%f, %f, %f)",
               octree->children[i]->minPoint.x, octree->children[i]->minPoint.y, octree->children[i]->minPoint.z,
               octree->children[i]->maxPoint.x, octree->children[i]->maxPoint.y, octree->children[i]->maxPoint.z);
    }
    printf("\np(%f, %f, %f)", point->x, point->y, point->z);

    printf("\n\n\tAlgo deu errado, não foi possivel encontrar o lugar para o ponto\n\n");
    getch();
    return NULL;
}

int isPointInsideBox(Octree *octree, Point *point) {
    // se for menor que omenor ou maior que o maior
    if(point->x < octree->minPoint.x || point->x > octree->maxPoint.x)
        return 0;
    if(point->y < octree->minPoint.y || point->y > octree->maxPoint.y)
        return 0;
    if(point->z < octree->minPoint.z || point->z > octree->maxPoint.z)
        return 0;

    return 1;
}

float halfX(Octree *octree) {
    return octree->minPoint.x + (octree->maxPoint.x - octree->minPoint.x)/2;
}
float halfY(Octree *octree) {
    return octree->minPoint.y + (octree->maxPoint.y - octree->minPoint.y)/2;
}
float halfZ(Octree *octree) {
    return octree->minPoint.z + (octree->maxPoint.z - octree->minPoint.z)/2;
}

void addMoleculePoint(Octree *octree, char *str) {
    char *delimiter = " ";

    strtok(str, delimiter);
    strtok(NULL, delimiter);

    Point *point = createPointFromStr(NULL);
    insertPoint(octree, point);
}

