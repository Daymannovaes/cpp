#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Point.h"
#include "Octree.h"

#include "ReadData.h"

char STOP_STR[2] = "-1";
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
    handler.octree->hasData = 0;
    //handler->binderNames = malloc(MAX_BINDERS * sizeof(char*));

    return handler;
}


void readAllBinders(FILE *file) {
    char *str;
    Point *binderPoint;
    do {
        str = readLineFrom(file);
        if(strIsBinderName(str)) {

            freeOctree(Handler.octree);
            Handler.octree = malloc(sizeof(Octree));
            Handler.octree->isLeaf = 1;
            Handler.octree->hasData = 0;
            //getch();

            str = readLineFrom(file);
            Handler.octree->minPoint = createPointFromStr(str);
            str = readLineFrom(file);
            Handler.octree->maxPoint = createPointFromStr(str);

        }
        else if(!strNull(str)) {
            if(strIsMoleculePoint(str)) {
                addMoleculePoint(Handler.octree, str);
                printf("\n addm \n");
            }
            else if(strIsBinderPoint(str)) {
                //addBinderPoint(binder, str);

                // compare with octree and update actual Binder
            }
        }
    } while(!stopReading(str, file));

    freeOctree(Handler.octree);
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}
int strNull(char *str) {
    return strlen(str) == 0;
}
