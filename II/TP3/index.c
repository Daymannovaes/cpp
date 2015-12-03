#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Point.h"
#include "Binder.h"
#include "Octree.h"

#include "ReadData.h"
#define MAX_BINDERS 100

char STOP_STR[2] = "-1";
void readAllBinders(FILE *file);
int stopReading(char *str, FILE *file);
int strNull(char *str);
void insertBinder(Binder binder);
void printBinders();
FILE *defineFile(/*char *fileName*/);

typedef struct {
    float edge;

    int binderCount;
    Binder *binders[MAX_BINDERS];
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
    //return fopen("input.txt", "r");
    return stdin;
}

THandler initHandler(float edge) {
    THandler handler;

    handler.edge = edge;
    handler.octree = malloc(sizeof(Octree));
    handler.binderCount = 0;

    return handler;
}


void readAllBinders(FILE *file) {
    char *str;
    Binder binder;
    int binderStength = 0;
    Point binderPoint, proteinPoint;
    Point pmin, pmax;
    Point origin, halfDimension;

    do {
        str = readLineFrom(file);

    // ---- initial configurations
        if(strIsBinderName(str)) {
        // ---- handling BINDER
            if(binderStength != 0) {
                binder.strength = binderStength;
                insertBinder(binder);
            }

            binderStength = 0;
            binder = createBinderFromStr(str);

        // ---- handling OCTREE
            freeOctree(Handler.octree);

            pmin = createPointFromStr(readLineFrom(file));
            pmax = createPointFromStr(readLineFrom(file));

            origin = calculateOrigin(pmax, pmin);
            halfDimension = calculateHalfDimension(origin, pmax);

            createOctree(&Handler.octree, origin, halfDimension);

        }
    // ---- processing POINTS
        else if(!strNull(str)) {
            if(strIsProteinPoint(str)) {
                proteinPoint = createPointFromInputLine(str);

                insertPoint(Handler.octree, proteinPoint);
            }
            else if(strIsBinderPoint(str)) {
                binderPoint = createPointFromInputLine(str);
                binderStength += getPointsInsideBox(binderPoint, Handler.octree, Handler.edge);
            }
        }
    } while(!stopReading(str, file));

    if(binderStength != 0) {
        binder.strength = binderStength;
        insertBinder(binder);
    }
    freeOctree(Handler.octree);
    printBinders();
}

void insertBinder(Binder binder) {
    int i, j;

    for(i=0; i<Handler.binderCount; i++) {
        if(binder.strength < Handler.binders[i]->strength)
            break; //use this actual value of i
    }

    Handler.binders[Handler.binderCount] = malloc(sizeof(Binder));
    Handler.binderCount++;

    //shift everyone
    for(j=Handler.binderCount-1; j>i; j--) {
        (*Handler.binders[j]) = (*Handler.binders[j-1]);
    }

    (*Handler.binders[i]) = binder;
}


void printBinders() {
    int i;
    for(i=0; i<Handler.binderCount; i++) {
        printf("%s %d\n", Handler.binders[i]->name, Handler.binders[i]->strength);
    }
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}
int strNull(char *str) {
    return str == NULL || strlen(str) == 0;
}
