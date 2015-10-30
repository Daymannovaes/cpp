#include "Message.h"

Message *createMessage(MessageKey key, char *text) {
    Message *message = malloc(sizeof(Message));

    message->key = key;

    message->text = malloc(strlen(text) + 1 * sizeof(char));
    strcpy(message->text, text);

    return message;
}
