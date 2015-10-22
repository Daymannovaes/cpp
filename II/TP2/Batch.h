#ifndef _BATCH_H
#define _BATCH_H

#include <stdio.h>
#include "Message.h"

typedef int TalkId;
typedef struct MessageBatchCell *BatchPointer;
typedef struct MessageBatchCell {
    Message message;
    TalkId talkId;

    BatchPointer next;
} MessageBatchCell;

typedef struct {
    BatchPointer first, last;
} MessageBatchList;

typedef int BatchId;
typedef struct {
     BatchId id;
     MessageBatchList messageBatchList;
} Batch;


// ---- LIST METHODS
Batch *createBatch(BatchId id);
MessageBatchList *createList();
void isEmpty(MessageBatchList list);
void insertInEndOfBatch(Message message, TalkId talkId, MessageBatchList *list);

// ---- BATCH METHODS
int strIsBatchInit(char *str);
int strIsBatchEnd(char *str);
void initBatch(char *str, FILE *file);
Batch *createBatch(BatchId id);
getBatchId(char *str);

// ---- BOTH
void readMessages(Batch *batch, FILE *file);

#endif
