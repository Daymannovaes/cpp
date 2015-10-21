#include <stdio.h>
#include <stdlib.h>

#include "Talk.h"
#include "Batch.h"

#include "ReadData.h"

FILE *defineFile(/*char *fileName*/) {
    return stdin;
}

char STOP_STR[2] = "-1";
int stopReading(FILE *file, char *str) {
    return feof(file) || !strcmp(str, STOP_STR);
}

int main() {
    Talk *talks;
    int maxBatchesWithoutMessage;

    FILE *file = defineFile();

    maxBatchesWithoutMessage = defineMaxBatchesWithoutMessage(file);
    readData(file, talks);
}

void readAllBatches(FILE *file) {
    char str[1024];

    do {
        str = readLineFrom(file);
    } while(!stopReading(file, str));
}
