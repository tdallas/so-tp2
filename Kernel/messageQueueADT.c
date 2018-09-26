#include "include/messageQueueADT.h"
#include "include/message.h"
#include "include/processes.h"
#include "include/lib.h"


struct queueHeader{
  int ownerPid;
  struct node * first;
  struct node * last;
  int waitingForPid;
  int messageSize;
};

struct node{
  struct node * tail;
  struct node * head;
  struct msg * message;
};


int isMessageAvailable(struct node * curr, int pid, int length){
  int aux = 0;
  for(; curr != NULL; curr = curr->tail){
    if(curr->message->pid == pid){
      aux += curr->message->length;
      if(aux >= length){
        return 1;
      }
    }
  }
  return 0;
}

struct node * searchMessageR(struct node* curr, messageQueueADT queue, struct node* prev, int pid, int length, char * dest){
  if(curr == NULL)
    return curr;

  curr->head = prev;
  if(curr->message->pid == pid){
    if(length >= curr->message->length){
      memcpy(dest, curr->message->msg, curr->message->length);
      length-=curr->message->length;
      dest += curr->message->length;

      struct node * aux = searchMessageR(curr->tail, queue, prev, pid, length, dest);
      free(curr->message->msg);
      free(curr->message);
      free(curr);
      return aux;

    }else{
      memcpy(dest, curr->message->msg, length);
      memcpy(curr->message->msg, curr->message->msg+length, curr->message->length-length);
      curr->message->length -= length;
      return curr;
    }
  }else{
    curr->tail = searchMessageR(curr->tail,queue, curr, pid, length, dest);
    if(curr->tail == NULL)
      queue->last = curr;
    return curr;
  }


}

void searchMessage(messageQueueADT queue, int pid, int length, char* dest){
  queue->first = searchMessageR(queue->first, queue,  NULL, pid, length, dest);
}

messageQueueADT newMessageQueue(int pid){
  struct queueHeader* newQueue = malloc(sizeof(struct queueHeader));
  newQueue->ownerPid = pid;
  newQueue->first = NULL;
  newQueue->last = NULL;
  newQueue->waitingForPid = -1;
  return (messageQueueADT)newQueue;
}

void sendMessage(messageQueueADT queue, int pid, char * text, int length){
  char * message = malloc(length);
  memcpy(message, text, length);
  struct node *newNode = malloc(sizeof(struct node));
  newNode->tail = NULL;
  newNode->head = queue->last;
  newNode->message = malloc(sizeof(struct msg));
  newNode->message->pid = pid;
  newNode->message->msg = message;
  newNode->message->length = length;

  if(queue->first == NULL){
    queue->first = newNode;
    queue->last = newNode;
  }else{
    queue->last->tail = newNode;
    queue->last = newNode;
  }

  if(pid == queue->waitingForPid && isMessageAvailable(queue->first, pid, queue->messageSize-length)){
    //*** Unblock process ***
    process *p = getProcessByPid(queue->ownerPid);
    unblockProcess(p);
  }
}

void receiveMessage(messageQueueADT queue, int pid, char* dest, int length){
  if(isMessageAvailable(queue->first, pid, length) == 0){
    //*** Block process ***
    queue->waitingForPid=pid;
    queue->messageSize = length;
    process *p = getProcessByPid(queue->ownerPid);
    blockProcess(p);
    yieldProcess();
    receiveMessage(queue, pid, dest, length);
  }else{
    searchMessage(queue, pid, length, dest);
  }
}