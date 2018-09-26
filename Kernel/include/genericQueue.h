
#ifndef GENERIC_QUEUE_H_
#define GENERIC_QUEUE_H_

typedef void *queueElement;

typedef struct queue *queueADT;

queueADT createQueue();

void deleteQueue(queueADT q);

int queueIsEmpty(queueADT queue);

void enqueue(queueADT queue, queueElement element);

queueElement dequeue(queueADT queue);

queueElement peek(queueADT queue);

#endif
