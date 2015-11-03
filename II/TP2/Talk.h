#ifndef _TALK_H
#define _TALK_H

#include "Message.h"

typedef struct MessageTalkCell *TalkPointer;
typedef struct MessageTalkCell {
     Message message;
     TalkPointer next;
} MessageTalkCell;

typedef struct {
    TalkPointer first, last;
} MessageTalkList;

typedef int TalkId;
typedef struct {
     TalkId id;
     MessageTalkList messageTalkList;
     int messagesSent; //0
     int lastBatchIdWithMessage;
} Talk;

void insertMessage(Message message, Talk *talk);
MessageTalkList *createMessageTalkList();
Talk *createTalk(int talkId, int batchId);
int messageIsBetween(Message message, TalkPointer pointer, TalkPointer next);
void insertAfterPointer(Message message, MessageTalkList *list, TalkPointer pointer);

Message *removeMessage(Talk *talk);

#endif
