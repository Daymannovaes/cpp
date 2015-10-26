#include <stdio.h>
#include "Talk.h"

MessageTalkList *createMessageTalkList() {
    MessageTalkList *list = malloc(sizeof(MessageTalkList));
    list->first = malloc(sizeof(MessageTalkCell));
    list->last = list->first;
    list->first->next = NULL;

    return list;
}

Talk *createTalk(int talkId) {
    Talk *talk;
    talk = malloc(sizeof(Talk));

    talk->id = talkId;
    talk->messagesSent = 0;
    talk->messageTalkList = *createMessageTalkList();

    return talk;
}


void insertMessage(Message message, Talk *talk) {
    TalkPointer pointer = talk->messageTalkList.first->next;
    TalkPointer next, aux;

    while(pointer != NULL) {
        next = pointer->next;

        if(messageIsBetween(message, pointer, next)) {
            printf("Inserindo mensagem %d entre %d e %d\n", message.key, pointer->message.key, next->message.key);
            insertAfterPointer(message, &talk->messageTalkList, pointer);
            return;
        }

        pointer = pointer->next;
    }

    printf("Inserindo (%d) no final: %s |||\n", message.key, message.text);
    insertAfterPointer(message, &talk->messageTalkList, talk->messageTalkList.last);
}

int messageIsBetween(Message message, TalkPointer pointer, TalkPointer next) {
    if(pointer == NULL || &pointer->message == NULL || next == NULL || &next->message == NULL)
        return 0;
    return (message.key > pointer->message.key && message.key < next->message.key);
}

void insertAfterPointer(Message message, MessageTalkList *list, TalkPointer pointer) {
     TalkPointer aux = malloc(sizeof(MessageTalkCell));
     aux->message = message;
     aux->next = pointer->next;

     if (aux->next == NULL)
        list->last = aux;

     pointer->next = aux;
}
