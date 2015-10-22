#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Talk.h"
#include "Batch.h"

#include "ReadData.h"

FILE *defineFile(/*char *fileName*/);

char STOP_STR[2] = "-1";
int stopReading(char *str, FILE *file);

int main() {
    Talk *talks;
    int maxBatchesWithoutMessage;

    FILE *file = defineFile();

    maxBatchesWithoutMessage = defineMaxBatchesWithoutMessage(file);
    readAllBatches(file);
}

FILE *defineFile(/*char *fileName*/) {
    return stdin;
}

void readAllBatches(FILE *file) {
    char *str;

    do {
        str = readLineFrom(file);
        if(strIsBatchInit(str)) {
            initBatch(str, file); //Batch.c
        }
    } while(!stopReading(str, file));
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}
