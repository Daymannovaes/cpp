#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Molecule.h"
#include "Binder.h"

#include "ReadData.h"

char STOP_STR[2] = "-1";
int stopReading(char *str, FILE *file);
FILE *defineFile(/*char *fileName*/);

int MAX_BINDERS = 100;
typedef struct {
    int binderCounter;
    Binder *binder; //array of binders
    float edge;

    Point minorPoint, majorPoint;
} THandler;

THandler *initHandler(float edge);

THandler Handler;
int main() {
    FILE *file = defineFile();
    float edge = defineEdge(file); //readData.c

    Handler = *initHandler(edge);
    readAllBinders(file);

    return 0;
}
FILE *defineFile(/*char *fileName*/) {
    //return fopen("input.txt", "r");
    return stdin;
}

THandler *initHandler(float edge) {
    THandler *handler;
    handler = malloc(sizeof(THandler));

    handler->binderCounter = 0;
    handler->binder = malloc(MAX_BINDERS * sizeof(Binder));
    handler->edge = edge;

    return handler;
}


void readAllBinders(FILE *file) {
    char *str;
    Binder *binder;

    do {
        str = readLineFrom(file);
        if(strIsBinderName(str)) {
            binder = createBinder(str + 6 * sizeof(char));


            printf("binder name %s", binder->name);
        }
        else {
            //binder or protein point
        }
    } while(!stopReading(str, file));
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}
