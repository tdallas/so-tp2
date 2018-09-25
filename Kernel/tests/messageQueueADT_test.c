#include "../include/messageQueueADT.h"
#include "../include/message.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>


void test1();

int main(){
  test1();
}

void test1(){
  struct msg receivedMsg;
  messageQueueADT new = newQueue(1000);

  char * strMsg =  "hola como andas!";
  struct msg newMsg = {10, strMsg, strlen(strMsg)+1};

  receivedMsg = receiveMessage(new, 10);
  assert(strcmp(strMsg, receivedMsg.msg)!=0);

  sendMessage(new, &newMsg);

  receivedMsg = receiveMessage(new, 8);
  assert(receivedMsg.pid == -1);

  receivedMsg = receiveMessage(new, -1);
  assert(receivedMsg.pid == -1);

  receivedMsg = receiveMessage(new, 10);
  assert(strcmp(strMsg, receivedMsg.msg)==0);

  receivedMsg = receiveMessage(new, 10);
  assert(strcmp(strMsg, receivedMsg.msg)!=0);

  struct msg newMsg2 = {9, strMsg, strlen(strMsg)+1};
  sendMessage(new, &newMsg2);

  struct msg newMsg3 = {8, strMsg, strlen(strMsg)+1};
  sendMessage(new, &newMsg3);

  struct msg newMsg4 = {7, strMsg, strlen(strMsg)+1};
  sendMessage(new, &newMsg4);

  receivedMsg = receiveMessage(new, 10);
  assert(strcmp(strMsg, receivedMsg.msg)!=0);

  receivedMsg = receiveMessage(new, 7);
  assert(strcmp(strMsg, receivedMsg.msg)==0);

  receivedMsg = receiveMessage(new, 7);
  assert(strcmp(strMsg, receivedMsg.msg)!=0);

  receivedMsg = receiveMessage(new, 9);
  assert(strcmp(strMsg, receivedMsg.msg)==0);

  receivedMsg = receiveMessage(new, 8);
  assert(strcmp(strMsg, receivedMsg.msg)==0);
}
