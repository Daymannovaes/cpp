#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Talk.h"
#include "Batch.h"

#include "ReadData.h"

int MAX_TALKS = 50;
typedef struct {
    Talk *talk; //array of talks
    int count; //number of talks
    int maxBatchesWithoutMessage;
} THandler;
THandler *initTalks(int maxBatchesWithoutMessage);
void pushTalk(Talk talk);
void removeTalk(int talkId);
int hasTalk(int talkId);
Talk *getTalk(int talkId);
int talkIndex(int talkId);

Talk *getPriorityTalk();

void readAllBatches(FILE *file);
void createTalkAndInsertMessage(Message message, int talkId, int batchId);
void deleteTalksWithFewMessages(int lastBatchId);

FILE *defineFile(/*char *fileName*/);

char STOP_STR[2] = "-1";
int stopReading(char *str, FILE *file);
void handleBatch(Batch *batch);

void batchToTalks(Batch *batch);
void printTalks();
void sendAndPrint();
void printCounters();

THandler Handler;
int main() {
    FILE *file = defineFile();
    int maxBatchesWithoutMessage = defineMaxBatchesWithoutMessage(file);

    Handler = *initTalks(maxBatchesWithoutMessage);
    readAllBatches(file);

    return 0;
}

THandler *initTalks(int maxBatchesWithoutMessage) {
    THandler *handler;
    handler = malloc(sizeof(THandler));

    handler->talk = malloc(MAX_TALKS * sizeof(Talk));
    handler->count = 0;
    handler->maxBatchesWithoutMessage = maxBatchesWithoutMessage;

    return handler;
}
void pushTalkInHandler(Talk talk) {
    Handler.count++;

    //Handler.talk = realloc(Handler.talk, Handler.count * sizeof(Talk));

//    Handler.talk[Handler.count-1] = malloc(sizeof(Talk));
    //printf("count %d\n", Handler.count-1);
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
        //Handler.talk = realloc(Handler.talk, Handler.count * sizeof(Talk));
    }
}
int hasTalk(int talkId) {
    return talkIndex(talkId) != -1;
}
Talk *getTalk(int talkId) {
    int i = talkIndex(talkId);
    if(i != -1)
        return &Handler.talk[talkIndex(talkId)];

    Talk *talk = NULL;
    return talk;
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
    //return fopen("input.txt", "r");
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
            getche();
        }
    } while(!stopReading(str, file));
}

int stopReading(char *str, FILE *file) {
    return feof(file) || !strcmp(str, STOP_STR);
}

void handleBatch(Batch *batch) {
    printf("Lote_%d:\n", batch->id);

    batchToTalks(batch);
    printTalks();
    sendAndPrint();
    printCounters();
}
void batchToTalks(Batch *batch) {
    int talkI, batchId;

    batchId = batch->id;
    BatchPointer pointer = batch->messageBatchList.first->next;
    while(pointer != NULL) {
        talkI= talkIndex(pointer->talkId);

        Handler.talk[talkI].lastBatchIdWithMessage = batchId;

        if(talkI != -1) {
            insertMessage(pointer->message, &Handler.talk[talkI]); //talk.c
        }
        else {
            createTalkAndInsertMessage(pointer->message, pointer->talkId, batchId);
        }
        pointer = pointer->next;

    }

    deleteTalksWithFewMessages(batchId);
}
void printTalks() {
    printf("Listas:\n");

    int i = 0, j = 0, c;
    TalkPointer pointer;
    Talk *talk;
    c = Handler.count;

    while(j < c) {
        talk = getTalk(i);
        if(talk != NULL) {
            printf("Par_%d:[", i);

            pointer = talk->messageTalkList.first->next;
            while(pointer != NULL) {
                printf("(%d,%s)", pointer->message.key, pointer->message.text);

                pointer = pointer->next;
                if(pointer != NULL)
                    printf(",");
            }
            printf("]\n");
            j++;
        }
        i++;
    }
}


void sendAndPrint() {
    printf("Envios:\n");

    Talk *talk = getPriorityTalk();
    Message *message = removeMessage(talk);

    while(talk != NULL && message != NULL) {
        printf("%d;%d;%s\n", talk->id, message->key, message->text);

        //free(message);
        talk = getPriorityTalk();
        if(talk != NULL)
            message = removeMessage(talk);
    }

}
void printCounters() {
    printf("Contadores:\n");

    int i = 0, j = 0, c;
    Talk *talk;
    c = Handler.count;

    while(j < c) {
        talk = getTalk(i);
        if(talk != NULL) {
            printf("Par_%d:%d\n", i, talk->messagesSent);
            j++;
        }

        i++;
    }
}

void createTalkAndInsertMessage(Message message, int talkId, int batchId) {
    Talk talk = *createTalk(talkId, batchId); //talk.c

    pushTalkInHandler(talk);
    insertMessage(message, &Handler.talk[Handler.count-1]); //talk.c
}

Talk *getPriorityTalk() {
    int i, c;
    c = Handler.count;
    if(!c)
        return NULL;

    int smallerCounter = Handler.talk[0].messagesSent;
    int betterId = Handler.talk[0].id;
    int index = 0;

    for(i=1; i<c; i++) {
        if(Handler.talk[i].messagesSent == smallerCounter) {
            if((Handler.talk[i].id < betterId)
               || (Handler.talk[index].messageTalkList.first == NULL || Handler.talk[index].messageTalkList.first->next == NULL || Handler.talk[index].messageTalkList.first->next->message.key != (Handler.talk[index].messagesSent + 1))) {
                if(Handler.talk[i].messageTalkList.first != NULL && Handler.talk[i].messageTalkList.first->next != NULL && Handler.talk[i].messageTalkList.first->next->message.key == (Handler.talk[i].messagesSent + 1)) {
                    betterId = Handler.talk[i].id;
                    index = i;
                }
            }
        }
        if((Handler.talk[i].messagesSent < smallerCounter)
           || (Handler.talk[index].messageTalkList.first == NULL || Handler.talk[index].messageTalkList.first->next == NULL || Handler.talk[index].messageTalkList.first->next->message.key != (Handler.talk[index].messagesSent + 1))) {
            if(Handler.talk[i].messageTalkList.first != NULL && Handler.talk[i].messageTalkList.first->next != NULL && Handler.talk[i].messageTalkList.first->next->message.key == (Handler.talk[i].messagesSent + 1)) {
                smallerCounter = Handler.talk[i].messagesSent;
                betterId = Handler.talk[i].id;
                index = i;
            }
        }
    }

    return &Handler.talk[index];
}

void deleteTalksWithFewMessages(int lastBatchId) {
    int i, c, diff;
    c = Handler.count;

    for(i=0; i<c; i++) {
        diff = lastBatchId - Handler.talk[i].lastBatchIdWithMessage;
        if(diff >= Handler.maxBatchesWithoutMessage) {
            removeTalkInHandler(Handler.talk[i].id);
            return;
        }
    }
}
