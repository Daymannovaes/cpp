#include "Message.h"

Message *createMessage(MessageKey key, char *text) {
    Message *message = malloc(sizeof(Message));

    message->key = key;

    message->text = malloc(strlen(text) * sizeof(char));
    strcpy(message->text, text);

    return message;
}
