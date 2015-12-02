#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Point.h"
#include "Octree.h"

#include "ReadData.h"

char STOP_STR[2] = "-1";
void readAllBinders(FILE *file);
int stopReading(char *str, FILE *file);
int strNull(char *str);
FILE *defineFile(/*char *fileName*/);

int MAX_BINDERS = 100;
typedef struct {
    float edge;

    //char **binderNames;
    Octree *octree;
} THandler;

THandler initHandler(float edge);

THandler Handler;
int main() {
    FILE *file = defineFile();
    float edge = defineEdge(file); //readData.c

    Handler = initHandler(edge);
    readAllBinders(file);

    return 0;
}
FILE *defineFile(/*char *fileName*/) {
    return fopen("input.txt", "r");
    return stdin;
}

THandler initHandler(float edge) {
    THandler handler;

    handler.edge = edge;
    handler.octree = malloc(sizeof(Octree));
    handler.octree->isLeaf = 1;
    //handler->binderNames = malloc(MAX_BINDERS * sizeof(char*));

    return handler;
}


void readAllBinders(FILE *file) {
    char *str;
    int sum;
    Point binder;
    Point pmin, pmax;
    Point origin, halfDimension;

    do {
        str = readLineFrom(file);

        if(strIsBinderName(str)) {
            freeOctree(Handler.octree);

            str = readLineFrom(file);
            pmin = createPointFromStr(str);
            str = readLineFrom(file);
            pmax = createPointFromStr(str);

            origin = calculateOrigin(pmax, pmin);
            halfDimension = calculateHalfDimension(origin, pmax);

            createOctree(&Handler.octree, origin, halfDimension);

            sum = 0;
        }
        else if(!strNull(str)) {
            if(strIsMoleculePoint(str)) {
                addMoleculePoint(Handler.octree, str);
            }
            else if(strIsBinderPoint(str)) {
                binder = createPointFromStr(str);

                getPointsInsideBox(binder, Handler.octree, Handler.edge, &sum);

                printf("\n sum: %d", sum);
            }
        }
    } while(!stopReading(str, file));

    freeOctree(Handler.octree);
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}
int strNull(char *str) {
    return str == NULL || strlen(str) == 0;
}
