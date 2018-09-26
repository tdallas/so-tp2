#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "message.h"

typedef struct queueHeader * messageQueueADT;

messageQueueADT newMessageQueue(int pid);

void sendMessage(messageQueueADT queue, int pid, char* text, int length);

void receiveMessage(messageQueueADT queue, int pid, char* dest, int length);

#endif
