#ifndef _TALK_H
#define _TALK_H

#include "Message.h"

typedef struct MessageTalkCell *TalkPointer;
typedef struct {
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
} Talk;

#endif
