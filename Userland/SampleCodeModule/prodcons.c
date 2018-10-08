#include <stdio.h>
#include <mutex.h>
#include <stdio.h>
#include <exitProcess.h>
#include <processExec.h>

#define MAX_CONSUMERS 5
#define MAX_PRODUCERS 5
#define MAX_ITEMS 10

static void*mutex;
static int items=0;
static int prod=0, cons=0;

void killProducer(){
  if(cons == 0 && prod==0){
    mutexClose(mutex);
    printf("Killing last child.\n");
    exitProcess();
  }

  mutexUnlock(mutex);
  printf("Killing producer.\n");
  exitProcess();
}

void killConsumer(){
  if(cons == 0 && prod==0){
    mutexClose(mutex);
    printf("Killing last child.\n");
    exitProcess();
  }

  mutexUnlock(mutex);
  printf("Killing consumer.\n");
  exitProcess();
}

void producer(int argc, char ** argv){
  int num = argc;
  while(1){
    mutexLock(mutex);
    if(num > prod){
      killProducer();
    }
    if(items < MAX_ITEMS){
      items++;
      printf("Producer (%d): item %d added.\n", num, items);
    }
    mutexUnlock(mutex);
  }
}

void consumer(int argc, char ** argv){
  int num = argc;
  while(1){
    mutexLock(mutex);
    if(num > cons){
      killConsumer();
    }
    if(items > 0){
      printf("Consumer (%d): item %d removed.\n",num, items);
      items--;
    }
    mutexUnlock(mutex);
  }
}

void killLastConsumer(){
  int flag =0;
  mutexLock(mutex);
  cons = cons>0?cons-1:0;
  if(prod == 0 && cons == 0)
    flag=1;
  mutexUnlock(mutex);
  if(flag){
    exitProcess();
    printf("Quiting.\n");
  }
}

void killLastProducer(){
  int flag =0;
  mutexLock(mutex);
  prod = prod>0?prod-1:0;
  if(prod == 0 && cons == 0)
    flag=1;
  mutexUnlock(mutex);
  if(flag){
    exitProcess();
    printf("Quiting.\n");
  }
}

void prodcons(){
  mutex = mutexInit("prodcons");
  printf("::: Prodcons :::\n");
  printf("'c'/'x' to add/remove consumer, 'p'/'o' to add/remove producer and 'q' to quit.\n\n");
  char c;
  while(1){
    c=getchar();
    switch (c) {
      case 'c':
        //add consumer
        mutexLock(mutex);
        if(cons < MAX_PRODUCERS){
          execProcess(consumer, cons+1, 0, 0, 0);
          cons++;
          printf("Added consumer (%d).\n", cons);

        }else{
          printf("Could not add consumer.\n");
        }
        mutexUnlock(mutex);
        break;
      case 'p':
        //add producer
        mutexLock(mutex);
        if(prod < MAX_PRODUCERS){
          execProcess(producer, prod+1, 0, 0, 0);
          prod++;
          printf("Added producer (%d).\n", prod);

        }else{
          printf("Could not add producer.\n");
        }
        mutexUnlock(mutex);
        break;
      case 'x':
        //remove consumer
        killLastProducer();
        break;
      case 'o':
        //remove producer
        killLastConsumer();
        break;
      case 'q':
        //quit
        printf("Quiting.\n");
        while(1){
          killLastConsumer();
          killLastProducer();
        }
        break;
      default:
        break;
    }
  }
}
