#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Talk.h"
#include "Batch.h"

#include "ReadData.h"

typedef struct {
    Talk *talk; //array of talks
    int count; //number of talks
    int maxBatchesWithoutMessage;
} THandler;
THandler *initTalks();
void pushTalk(Talk talk);
void removeTalk(int talkId);


FILE *defineFile(/*char *fileName*/);

char STOP_STR[2] = "-1";
int stopReading(char *str, FILE *file);
void handleBatch(Batch *batch);

void printTalks(Batch *batch);
void sendAndPrint(Batch *batch);
void printCounters(Batch *batch);

THandler Handler;
int main() {
    int maxBatchesWithoutMessage;

    Handler = *initTalks();
    FILE *file = defineFile();

    maxBatchesWithoutMessage = defineMaxBatchesWithoutMessage(file);
    readAllBatches(file);
}

THandler *initTalks() {
    THandler *handler;
    handler = malloc(sizeof(THandler));

    handler->talk = malloc(sizeof(Talk));
    handler->count = 0;

    return handler;
}
void pushTalkInHandler(Talk talk) {
    Handler.count++;
    Handler.talk = realloc(Handler.talk, Handler.count * sizeof(Talk));

    //Handler.talk[Handler.count-1] = malloc(sizeof(Talk));
    Handler.talk[Handler.count-1] = talk;
}
void removeTalkInHandler(int talkId) {
    int i, c;
    c = Handler.count;

    for(i=0; i<c; i++) {
        if(Handler.talk[i].id == talkId) {
            printf("remove");
        }
    }
}


FILE *defineFile(/*char *fileName*/) {
    return stdin;
}

void readAllBatches(FILE *file) {
    char *str;
    Batch *batch;

    do {
        str = readLineFrom(file);
        if(strIsBatchInit(str)) {
            batch = readBatch(str, file); //Batch.c

            handleBatch(batch);
        }
    } while(!stopReading(str, file));
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}

void handleBatch(Batch *batch) {
    printf("Lote %d\n", batch->id);

    printTalks(batch);
    sendAndPrint(batch);
    printCounters(batch);
}

void printTalks(Batch *batch) {
    printf("Listas:\n");
}
void sendAndPrint(Batch *batch) {
    printf("Envios:\n");
}
void printCounters(Batch *batch) {
    printf("Contadores:\n");
}
