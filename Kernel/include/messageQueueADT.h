#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "message.h"

typedef struct queueHeader * messageQueueADT;

messageQueueADT newQueue(int pid);

void sendMessage(messageQueueADT queue, struct msg * message);

struct msg receiveMessage(messageQueueADT queue, int pid);

#endif
