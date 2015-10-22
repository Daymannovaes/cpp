#ifndef _MESSAGE_H
#define _MESSAGE_H

typedef int MessageKey;
typedef struct {
     MessageKey key;
     char *text;
} Message;

Message *createMessage(MessageKey key, char *text);

#endif
