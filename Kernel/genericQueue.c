#include "./genericQueue.h"
#include <stdlib.h>

typedef struct node
{
  queueElement element;
  struct node *next;
} node;

struct queue
{
  node *first;
  node *last;
};

queueADT createQueue()
{
  queueADT queue = (queueADT)malloc(sizeof(*queue));
  if (queue == NULL)
    return NULL;
  queue->first = NULL;
  queue->last = NULL;
  return queue;
}

void deleteQueue(queueADT queue)
{
  while (!queueIsEmpty(queue))
  {
    dequeue(queue);
  }

  free(queue);
}

int queueIsEmpty(queueADT queue)
{
  return queue == NULL || queue->first == NULL;
}

void enqueue(queueADT queue, queueElement element)
{
  if (queue == NULL)
  {
    return;
  }

  node *auxNode = (node *)malloc(sizeof(*auxNode));
  auxNode->element = element;
  auxNode->next = NULL;

  if (queue->first == NULL)
  {
    queue->first = auxNode;
    queue->last = auxNode;
  }
  else
  {
    queue->last->next = auxNode;
    queue->last = auxNode;
  }
}

queueElement peek(queueADT queue)
{
  if (queueIsEmpty(queue))
  {
    return NULL;
  }

  return queue->first->element;
}

queueElement dequeue(queueADT queue)
{
  if (queueIsEmpty(queue))
  {
    return NULL;
  }

  node *auxFirst = queue->first;
  queueElement element;
  element = queue->first->element;
  queue->first = queue->first->next;

  if (queue->first == NULL)
  {
    queue->last = NULL;
  }

  free(auxFirst);
  return element;
}
