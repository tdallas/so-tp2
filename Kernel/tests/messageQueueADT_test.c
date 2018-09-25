#include "../include/messageQueueADT.h"
#include "../include/message.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>


void test1();
void test2();
void test3();

int main(){
  test1();
  test2();
  test3();
}

void test1(){
  messageQueueADT queue = newMessageQueue(10);

  char * msg1 = "hola como andas.";
  sendMessage(queue, 9, msg1, strlen(msg1));

  char response1[5];
  receiveMessage(queue, 9, response1, 5);
  assert(strcmp("hola ", response1) == 0);

  char response2[5];
  receiveMessage(queue, 9, response2, 5);
  assert(strcmp("como ", response2) == 0);

  char response3[6];
  receiveMessage(queue, 9, response3, 6);
  assert(strcmp("andas.", response3) == 0);
}

void test2(){
  messageQueueADT queue = newMessageQueue(10);

  char * msg1 = "hola";
  sendMessage(queue, 9, msg1, strlen(msg1));

  char response[9];
  char responseBackup[9];
  responseBackup[8]=0;
  response[8]=0;
  memcpy(responseBackup, response, 8);
  receiveMessage(queue, 9, response, 8);
  assert(strcmp(responseBackup, response) == 0);

  char * msg2 = "como";
  sendMessage(queue, 9, msg2, strlen(msg2));

  receiveMessage(queue, 9, response, 8);
  assert(strcmp("holacomo", response) == 0);
}

void test3(){
  messageQueueADT queue1 = newMessageQueue(10);

  char * msg1 = "hola   ";
  sendMessage(queue1, 9, msg1, strlen(msg1));

  char response[9];
  char responseBackup[9];
  responseBackup[8]=0;
  response[8]=0;
  memcpy(responseBackup, response, 8);
  receiveMessage(queue1, 8, response, 4);
  assert(strcmp(responseBackup, response) == 0);

}
