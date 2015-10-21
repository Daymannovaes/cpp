#ifndef _BATCH_H
#define _BATCH_H

#include "Message.h"

typedef struct MessageBatchCell *BatchPointer;
typedef int TalkId;
typedef struct {
    Message message;
    TalkId talkId;

    BatchPointer next;
} MessageBatchCell;

typedef struct {
    BatchPointer first, last;
} MessageBatchList;

typedef int Id;
typedef struct {
     Id id;
     MessageBatchList messageBatchList;
} Batch;

#endif
