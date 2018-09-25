#include "include/messageQueueADT.h"
#include "include/message.h"
#include "include/processes.h"
#include "include/lib.h"


struct queueHeader{
  int ownerPid;
  struct node * first;
  struct node * last;
  int waitingForPid;
};

struct node{
  struct node * tail;
  struct node * head;
  struct msg * message;
};

struct node *searchMessage(messageQueueADT queue, int pid){
  for(struct node* aux = queue->first; aux != NULL ; aux = aux->tail){
    if(aux->message->pid == pid){
      return aux;
    }
  }
  return NULL;
}

messageQueueADT newQueue(int pid){
  struct queueHeader* newQueue = malloc(sizeof(struct queueHeader));
  newQueue->ownerPid = pid;
  newQueue->first = NULL;
  newQueue->last = NULL;
  newQueue->waitingForPid = -1;
  return (messageQueueADT)newQueue;
}

void sendMessage(messageQueueADT queue, struct msg * message){

  struct node *newNode = malloc(sizeof(struct node));
  newNode->tail = NULL;
  newNode->head = queue->last;
  newNode->message = message;

  if(queue->first == NULL){
    queue->first = newNode;
    queue->last = newNode;
  }else{
    queue->last->tail = newNode;
    queue->last = newNode;
  }

  if(message->pid == queue->waitingForPid){
    //*** Unblock process ***
    // process *p = getProcessByPid(queue->ownerPid);
    // unblockProcess(p);
  }
}

struct msg receiveMessage(messageQueueADT queue, int pid){
  struct node * pendingMessage = searchMessage(queue, pid);
  if(pendingMessage == NULL){
    queue->waitingForPid = pid;
    //*** Block process ***
    // process *p = getProcessByPid(queue->ownerPid);
    // blockProcess(p);
    struct msg mensaje = {-1, "", 0};
    return mensaje;
  }else{
    if(pendingMessage->head != NULL){
      pendingMessage->head->tail = pendingMessage->tail;
    }else{
      queue->first = pendingMessage->tail;
    }

    if(pendingMessage->tail != NULL){
      pendingMessage->tail->head = pendingMessage->head;
    }else{
      queue->last = pendingMessage->head;
    }

    struct msg aux = *(pendingMessage->message);
    free(pendingMessage);
    return aux;
  }
}
