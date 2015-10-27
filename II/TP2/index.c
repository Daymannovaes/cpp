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
THandler *initTalks(int maxBatchesWithoutMessage);
void pushTalk(Talk talk);
void removeTalk(int talkId);
int hasTalk(int talkId);
int talkIndex(int talkId);

void createTalkAndInsertMessage(Message message, int talkId);


FILE *defineFile(/*char *fileName*/);

char STOP_STR[2] = "-1";
int stopReading(char *str, FILE *file);
void handleBatch(Batch *batch);

void batchToTalks(Batch *batch);
void printTalks(Batch *batch);
void sendAndPrint(Batch *batch);
void printCounters(Batch *batch);

THandler Handler;
int main() {
    FILE *file = defineFile();
    int maxBatchesWithoutMessage = defineMaxBatchesWithoutMessage(file);

    Handler = *initTalks(maxBatchesWithoutMessage);

    readAllBatches(file);
}

THandler *initTalks(int maxBatchesWithoutMessage) {
    THandler *handler;
    handler = malloc(sizeof(THandler));

    handler->talk = malloc(sizeof(Talk));
    handler->count = 0;
    handler->maxBatchesWithoutMessage = maxBatchesWithoutMessage;

    return handler;
}
void pushTalkInHandler(Talk talk) {
    Handler.count++;
    Handler.talk = realloc(Handler.talk, Handler.count * sizeof(Talk));

    //Handler.talk[Handler.count-1] = malloc(sizeof(Talk));
    Handler.talk[Handler.count-1] = talk;
}
void removeTalkInHandler(int talkId) {
    int i, j, c;
    c = Handler.count;

    i = talkIndex(talkId);
    if(i != -1) {
        for(j=i; j<c-1; j++) { //shift everyone
            Handler.talk[j] = Handler.talk[j+1];
        }
        Handler.count--;
        Handler.talk = realloc(Handler.talk, Handler.count * sizeof(Talk));
    }
}
int hasTalk(int talkId) {
    return talkIndex(talkId) != -1;
}
int talkIndex(int talkId) {
    int i, c;
    c = Handler.count;

    for(i=0; i<c; i++) {
        if(Handler.talk[i].id == talkId) {
            return i;
        }
    }
    return -1;
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

    batchToTalks(batch);
    printTalks(batch);
    sendAndPrint(batch);
    printCounters(batch);
}
void batchToTalks(Batch *batch) {
    int talkI;
    BatchPointer pointer = batch->messageBatchList.first->next;
    while(pointer != NULL) {
        talkI= talkIndex(pointer->talkId);
        if(talkI != -1) {
            insertMessage(pointer->message, &Handler.talk[talkI]); //talk.c
        }
        else {
            createTalkAndInsertMessage(pointer->message, pointer->talkId);
        }
        pointer = pointer->next;
    }
}
void printTalks(Batch *batch) {
    printf("Listas:\n");

    int i, c;
    TalkPointer pointer;
    c = Handler.count;

    for(i=0; i<c; i++) {
        printf("Par_%d:[", i);

        pointer = Handler.talk[i].messageTalkList.first->next;
        while(pointer != NULL) {
            printf("(%d,%s)", pointer->message.key, pointer->message.text);

            pointer = pointer->next;
            if(pointer != NULL)
                printf(", ");
        }

        printf("]\n");
    }
}


void sendAndPrint(Batch *batch) {
    printf("Envios:\n");
}
void printCounters(Batch *batch) {
    printf("Contadores:\n");
}

void createTalkAndInsertMessage(Message message, int talkId) {
    Talk talk = *createTalk(talkId); //talk.c

    pushTalkInHandler(talk);
    insertMessage(message, &Handler.talk[Handler.count-1]); //talk.c
}
