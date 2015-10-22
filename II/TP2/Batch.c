#include <string.h>
#include "Batch.h"

// ---- LIST METHODS
MessageBatchList *createList() {
    MessageBatchList *list = malloc(sizeof(MessageBatchList));
    list->first = malloc(sizeof(MessageBatchCell));
    list->last = list->first;
    list->first->next = NULL;

    return list;
}
void isEmpty(MessageBatchList list) {
    return list.first == list.last;
}
void insertInEndOfBatch(Message message, TalkId talkId, MessageBatchList *list) {
    list->last->next = malloc(sizeof(MessageBatchCell));
    list->last = list->last->next;

    list->last->talkId = talkId;
    list->last->message = message;
    list->last->next = NULL;
}

// ---- BATCH METHODS
int strIsBatchInit(char *str) {
    return strstr(str, "Lote ") != NULL;
}
void initBatch(char *str, FILE *file) {
    int id = getBatchId(str);
    Batch *batch = createBatch(id);

    readMessages(batch, file);
}
Batch *createBatch(BatchId id) {
    Batch *batch = malloc(sizeof(Batch));

    batch->id = id;
    batch->messageBatchList = *createList();

    return batch;
}
int getBatchId(char *str) {
    str += 5 * sizeof(char);
    return atoi(str);
}
void readMessages(Batch *batch, FILE *file) {
    char *str;
    char *delimiter = ";";

    int talkId, messageKey;
    char *text;

    str = readLineFrom(file);
    while(!strIsBatchEnd(str)) {
        talkId = atoi(strtok(str, delimiter));
        messageKey = atoi(strtok(NULL, delimiter));
        text = strtok(NULL, "\n");

        Message message = *createMessage(messageKey, text);

        insertInEndOfBatch(message, talkId, &batch->messageBatchList);

        str = readLineFrom(file);
    }
}
int strIsBatchEnd(char *str) {
    return (strstr(str, "Fim") != NULL && strlen(str) == 3);
}
